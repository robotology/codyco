/*
 * Copyright (C) 2013  CoDyCo Consortium
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
 *
 * Authors: Andrea Del Prete, Marco Randazzo
 * email: andrea.delprete@iit.it - marco.randazzo@iit.it
 */

#include <wbi/wbi.h>
#include <sstream>

using namespace std;
using namespace wbi;

LocalIdList::LocalIdList()
{}
LocalIdList::LocalIdList(int bp, int j0)
{ pushId(bp,j0); }
LocalIdList::LocalIdList(int bp, int j0, int j1)
{ pushId(bp,j0); pushId(bp,j1);}
LocalIdList::LocalIdList(int bp, int j0, int j1, int j2)
{ pushId(bp,j0); pushId(bp,j1); pushId(bp,j2); }
LocalIdList::LocalIdList(int bp, int j0, int j1, int j2, int j3)
{ pushId(bp,j0); pushId(bp,j1); pushId(bp,j2); pushId(bp,j3); }
LocalIdList::LocalIdList(int bp, int j0, int j1, int j2, int j3, int j4)
{ pushId(bp,j0); pushId(bp,j1); pushId(bp,j2); pushId(bp,j3); pushId(bp,j4); }
LocalIdList::LocalIdList(int bp, int j0, int j1, int j2, int j3, int j4, int j5)
{ pushId(bp,j0); pushId(bp,j1); pushId(bp,j2); pushId(bp,j3); pushId(bp,j4); pushId(bp,j5); }
LocalIdList::LocalIdList(int bp, int j0, int j1, int j2, int j3, int j4, int j5, int j6)
{ pushId(bp,j0); pushId(bp,j1); pushId(bp,j2); pushId(bp,j3); pushId(bp,j4); pushId(bp,j5); pushId(bp,j6); }

void LocalIdList::pushId(int bp, int i)
{
    (*this)[bp].push_back(i);
}

/** Convert a local id into a global id */
int LocalIdList::localToGlobalId(const LocalId &i)
{
    int gid = 0;
    FOR_ALL_BODY_PARTS_OF(itBp, (*this))
        if(itBp->first == i.bodyPart)
        {
            FOR_ALL_JOINTS(itBp, itJ)
                if(i.index == *itJ)
                    return gid;
                else
                    gid++;
        }
        else
            gid += itBp->second.size();
    return gid;
}

/** Convert a global id into a local id */
LocalId LocalIdList::globalToLocalId(int globalId)
{
    // iterate over list decreasing globalId for each id encountered
    // when globalId==0 => we found the local id
    FOR_ALL_BODY_PARTS_OF(itBp, (*this))
        if(globalId > (int)itBp->second.size())  // if globalId greater than # of ids of current body part 
            globalId -= itBp->second.size();
        else
        {
            FOR_ALL_JOINTS(itBp, itJ)
                if(globalId==0)
                    return LocalId(itBp->first, *itJ);
                else
                    globalId--;
        }
    return LocalId();
}

//Remove an existing joint 
bool LocalIdList::removeId(const LocalId &j)
{
    LocalIdList::iterator itBp = find(j.bodyPart);
    if(itBp == end())
        return false;
    FOR_ALL_JOINTS_NC(itBp, itJ)
    {
        if(j.index == *itJ)
        {
            itBp->second.erase(itJ);
            return true;
        }
    }
    return false;
}

bool LocalIdList::addId(const LocalId &i)
{
    if(containsId(i))
        return false;
    pushId(i.bodyPart, i.index);
    return true;
}

int LocalIdList::addIdList(const LocalIdList &jList)
{
    int count = 0;
    FOR_ALL_OF(itBp, itJ, jList)
        if(!containsId(LocalId(itBp->first,*itJ)))
        {
            pushId(itBp->first,*itJ);
            count++;
        }
    return count;
}

bool LocalIdList::containsId(const LocalId &i)
{
    if(find(i.bodyPart)==end())
        return false;
    vector<int> &v = (*this)[i.bodyPart];
    for(unsigned int j=0; j<v.size(); j++)
        if(v[j]==i.index)
            return true;
    return false;
}

// Get the number of ids in this list
unsigned int LocalIdList::size()
{
    unsigned int s=0;
    FOR_ALL_BODY_PARTS_OF(itBp, (*this))
        s += itBp->second.size();
    return s;
}

string LocalIdList::toString()
{
    stringstream s;
    FOR_ALL_BODY_PARTS_OF(itBp, (*this))
    {
        s << "(Body part "<< itBp->first<< " Joints ";
        FOR_ALL_JOINTS(itBp, itJ)
            s<< *itJ<< " ";
        s<< ") ";
    }
    return s.str();
}