using namespace std;

class IDAStarSearch
{


    bool IDDFS(int iniitalState, int goalState, int max_depth){

        //depth-limited search until max_depth
        while(max_depth)
            i=0;
            if(DLS(initialState, goalState, i)==true)
            return true;
        return false;

    }

    bool DLS(int initialState, int goalState, int limit){
        if (iniitalState==goalState)
            return true;

        if(limit <= 0)
            return false;

        //recursively traverse all nextnodes
        for (auto i = adj[initialState].begin(); i != adj[initialState].end(); i++))
            if (DLS(*i, goalState, limit-1) == true)
                return true;
        return false;
    }



}
