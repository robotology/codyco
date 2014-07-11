/* 
 * Copyright (C) 2013 CoDyCo
 * Author: Andrea Del Prete
 * email:  andrea.delprete@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

#include <wholeBodyReach/wbiConstraints.h>
#include <wholeBodyReach/Logger.h>
#include <Eigen/Geometry>

// TEMP
#include <yarp/os/Time.h>
using namespace yarp::math;
// END TEMP

using namespace wholeBodyReach;
using namespace std;
using namespace wbi;
using namespace Eigen;

/*********************************************************************************************************/
/******************************************* ContactConstraint *******************************************/
/*********************************************************************************************************/

ContactConstraint::ContactConstraint(std::string name, std::string linkName,
                                     int numberOfForces, int numberOfInequalityConstraints,
                                     wbi::wholeBodyInterface* robot)
:   WbiAbstractTask(name, numberOfForces, robot),
    WbiEqualityTask(numberOfForces, robot->getDoFs()+6),
    WbiInequalityTask(numberOfInequalityConstraints, numberOfForces),
    _linkName(linkName)
{
    setNormalDirection(Vector3d::UnitZ());
    _X.setIdentity(6, numberOfForces);
    if(!robot->getLinkId(linkName.c_str(), _linkId))
        cout<<"Error while trying to get the ID of link "<<linkName<<endl;
}

bool ContactConstraint::setNormalDirection(Vector3d normalDir)
{
    _normalDir = normalDir;
    _normalDir.normalize();
    if(_normalDir.norm()==0.0)
        return false;
    _tangentDir1 = _normalDir.cross(Vector3d::UnitY());
    _tangentDir1.normalize();
    _tangentDir2 = _normalDir.cross(_tangentDir1);
    _tangentDir2.normalize();
    return true;
}

void ContactConstraint::updateForceFrictionConeInequalities()
{
    // * 1 bilateral for Fn (written as 2 unilateral)
    _A_in.block<1,3>(0,0)   =   _normalDir.transpose();
    _A_in.block<1,3>(1,0)   = - _normalDir.transpose();
    _a_in(0)                = _fNormalMax;
    _a_in(1)                = _fNormalMin;
    
    // * 4 unilateral for linearized friction cone
    //  Ft < mu*Fn
    // -Ft < mu*Fn
    _A_in.block<1,3>(2,0)   =  _tangentDir1.transpose() - _muF*_normalDir.transpose();
    _A_in.block<1,3>(3,0)   = -_tangentDir1.transpose() - _muF*_normalDir.transpose();
    _A_in.block<1,3>(4,0)   =  _tangentDir2.transpose() - _muF*_normalDir.transpose();
    _A_in.block<1,3>(5,0)   = -_tangentDir2.transpose() - _muF*_normalDir.transpose();
    _a_in.segment<4>(2).setZero();
    
    cout<<"Force friction inequalities:\n"<< toString(_A_in.block(0,0,6,_m),1)<<endl;
    cout<<"< "<< toString(_a_in.segment<6>(0),1)<<endl;
}

void ContactConstraint::linkParameterForceFrictionCoefficient(ParamHelperServer* paramHelper, int paramId)
{
    paramHelper->linkParam(paramId, &_muF);
    paramHelper->registerParamValueChangedCallback(paramId, this);
    _paramId_muF = paramId;
}

void ContactConstraint::parameterUpdated(const ParamProxyInterface *pp)
{
    if(pp->id==_paramId_muF)
        updateForceFrictionConeInequalities();
}

/*********************************************************************************************************/
/************************************** PlaneContactConstraint *******************************************/
/*********************************************************************************************************/

PlaneContactConstraint::PlaneContactConstraint(std::string name, std::string linkName,
                                               const ContactPlaneSize &planeSize,
                                               wbi::wholeBodyInterface* robot)
:   ContactConstraint(name, linkName, 6, 12, robot),
    _planeSize(planeSize)
{
    _A_in.setZero(12, 6);
    _a_in.setZero(12);
    // 12 inequalities:
    // * 1 bilateral for Fz (counts as 2)
    // * 4 unilateral for linearized friction cone
    // * 4 unilateral for CoP (i.e. ZMP)
    // * 2 unilateral for normal moment
    
    updateZmpInequalities();    // update zmp inequalities because they are supposed to remain constant
}

bool PlaneContactConstraint::update(RobotState& state)
{
    bool res = true;
    // update equality matrix and equality vectory
    res = res && _robot->computeJacobian(state.qJ.data(), state.xBase, _linkId, _A_eq.data());
    res = res && _robot->computeDJdq(state.qJ.data(), state.xBase, state.dqJ.data(),
                                     state.vBase.data(), _linkId, _a_eq.data());
    _a_eq *= -1.0;  // _a_eq = -dJ*dq
    
    // compute force-momentum mapping matrix _X
    res = res && _robot->computeH(state.qJ.data(), state.xBase, _linkId, _H);
    res = res && _robot->computeH(state.qJ.data(), state.xBase, iWholeBodyModel::COM_LINK_ID, _Hcom);
    _p_com[0] = _H.p[0] - _Hcom.p[0];
    _p_com[1] = _H.p[1] - _Hcom.p[1];
    _p_com[2] = _H.p[2] - _Hcom.p[2];
    _X.bottomLeftCorner<3,3>() = crossProductMatrix(_p_com);
    
    return res;
}

void PlaneContactConstraint::updateZmpInequalities()
{
    // * 4 unilateral for ZMP
    //  -Fn*Ltn < Mt < Fn*Ltp
    // [0 0 -Lxp 1 0 0] f < 0
    // [0 0 -Lxn -1 0 0] f < 0
    // @todo Improve this implementation, which assumes contact plane is aligned with x-y axis
    _A_in(6,2)    = -_planeSize.xPos;
    _A_in(6,3)    = 1.0;
    _A_in(7,2)    = -_planeSize.xNeg;
    _A_in(7,3)    = -1.0;
    _A_in(8,2)    = -_planeSize.yPos;
    _A_in(8,4)    = 1.0;
    _A_in(9,2)    = -_planeSize.yNeg;
    _A_in(9,4)    = -1.0;
    _a_in.segment<4>(6).setZero();
    
    cout<<"Zmp inequalities:\n"<< toString(_A_in.block<4,6>(6,0),1)<<endl;
    cout<<"< "<< toString(_a_in.segment<4>(6),1)<<endl;
}

void PlaneContactConstraint::updateMomentFrictionConeInequalities()
{
    _normalDir.normalize();
    _tangentDir1 = _normalDir.cross(Vector3d::UnitY());
    _tangentDir1.normalize();
    _tangentDir2 = _normalDir.cross(_tangentDir1);
    _tangentDir2.normalize();
    
    // * 2 unilateral for linearized moment friction cone Mn (normal moment)
    //  Mn < mu*Fn
    // -Mn < mu*Fn
    _A_in.block<1,3>(10,0)  = - _muM * _normalDir.transpose();
    _A_in.block<1,3>(10,3)  =          _normalDir.transpose();
    _A_in.block<1,3>(11,0)  = - _muM * _normalDir.transpose();
    _A_in.block<1,3>(11,3)  = -        _normalDir.transpose();
    _a_in.segment<2>(10).setZero();
    
    cout<<"Moment friction inequalities:\n"<< toString(_A_in.block<2,6>(10,0),1)<<endl;
    cout<<"< "<< toString(_a_in.segment<2>(10),1)<<endl;
}

void PlaneContactConstraint::linkParameterMomentFrictionCoefficient(ParamHelperServer* paramHelper, int paramId)
{
    paramHelper->linkParam(paramId, &_muM);
    paramHelper->registerParamValueChangedCallback(paramId, this);
    _paramId_muM = paramId;
}

void PlaneContactConstraint::parameterUpdated(const ParamProxyInterface *pp)
{
    if(pp->id==_paramId_muM)
        updateMomentFrictionConeInequalities();
    else
        ContactConstraint::parameterUpdated(pp);
}

/*********************************************************************************************************/
/************************************** PointContactConstraint *******************************************/
/*********************************************************************************************************/

PointContactConstraint::PointContactConstraint(std::string name, std::string linkName,
                                               wbi::wholeBodyInterface* robot)
:   ContactConstraint(name, linkName, 3, 5, robot)
{
    _Jc.setZero(6, robot->getDoFs());
}

bool PointContactConstraint::update(RobotState& state)
{
    bool res = true;
    // update equality matrix and equality vectory
    res = res && _robot->computeJacobian(state.qJ.data(), state.xBase, _linkId, _Jc.data());
    _A_eq = _Jc.topRows<3>();
    res = res && _robot->computeDJdq(state.qJ.data(), state.xBase, state.dqJ.data(),
                                     state.vBase.data(), _linkId, _dJcdq.data());
    _a_eq = -_dJcdq.head<3>();
    
    // compute force-momentum mapping matrix _X
    res = res && _robot->computeH(state.qJ.data(), state.xBase, _linkId, _H);
    res = res && _robot->computeH(state.qJ.data(), state.xBase, iWholeBodyModel::COM_LINK_ID, _Hcom);
    _p_com[0] = _H.p[0] - _Hcom.p[0];
    _p_com[1] = _H.p[1] - _Hcom.p[1];
    _p_com[2] = _H.p[2] - _Hcom.p[2];
    _X.bottomLeftCorner<3,3>() = crossProductMatrix(_p_com);
    
    return res;
}



/*********************************************************************************************************/
/******************************************* UTILITIES ***************************************************/
/*********************************************************************************************************/

Eigen::MatrixR3d wholeBodyReach::crossProductMatrix(Eigen::VectorConst v)
{
    //  0 -z +y
    // +z  0 -x
    // -y +x  0
    MatrixR3d S;
    S(0,0) = S(1,1) = S(2,2) = 0.0;
    S(1,0) = v(2);
    S(2,0) = -v(1);
    S(2,1) = v(0);
    S(0,1) = -v(2);
    S(0,2) = v(1);
    S(1,2) = -v(0);
    return S;
}