


//refresher
//f(x)=h(x)+g(x)
/* g(x)=g(x.parent)+cost(x.parent,x)
h = heuristic for that node

*/

/* pseudo from https://algorithmsinsight.wordpress.com/graph-theory-2/ida-star-algorithm-in-general/

root=initial node;
Goal=final node;
function IDA*()                                             //Driver function
{

threshold=heuristic(Start);
while(1)             //run for infinity
{

integer temp=search(Start,0,threshold); //function search(node,g score,threshold)
if(temp==FOUND)                                 //if goal found
         return FOUND;
if(temp== ∞)                               //Threshold larger than maximum possible f value
         return;                               //or set Time limit exceeded
threshold=temp;

}

}
function Search(node, g, threshold)              //recursive function
{

f=g+heuristic(node);
if(f>threshold)             //greater f encountered
         return f;
if(node==Goal)               //Goal node found
         return FOUND;
integer min=MAX_INT;     //min= Minimum integer
foreach(tempnode in nextnodes(node))
{

//recursive call with next node as current node for depth search
integer temp=search(tempnode,g+cost(node,tempnode),threshold);
if(temp==FOUND)            //if goal found
return FOUND;
if(temp<min)     //find the minimum of all ‘f’ greater than threshold encountered                                min=temp;

}
return min;  //return the minimum ‘f’ encountered greater than threshold

}
function nextnodes(node)
{
             return list of all possible next nodes from node;
}


*/


class Node{
    public:
    int data;
    //int gval;
    //int hval; unsure if these are needed

    Node* next;
    Node* prev;
    //Node* left, right; - this is for a binary tree implementation, unsure if needexd

};
//TODO: everything, but try to figure out how to get the gvalue of the parent node - doubly linked list?

void push(Node **head, int data){
    //from https://www.geeksforgeeks.org/doubly-linked-list/
    //front of list

    Node* newnode = new Node();

    //TODO: unsure if data contains the h/gvals, if not then have to change newnode->data to newnode -> h/gval

    newnode->data = data;
    newnode->next = (*head);
    newnode->prev = nullptr;

    if(*head != nullptr){
        (*head)->prev = newnode;
    }

    (*head) = newnode;

}

//TODO: unsure if need to add fxns that insert before/after a given node

void append(Node ** head, int data){

    Node* newnode = new Node();
    Node* last = *head;

    newnode->data = data;
    newnode->next = nullptr;
    //newnode->prev = nullptr;


    if (*head == nullptr)
    {
        newnode->prev = nullptr;
        *head = newnode;
        return;
    }

    while (last->next != nullptr)
        last = last->next;

    last->next = newnode;

    newnode->prev = last;

}
//This search alg does a dfs at each iter and if depth exceeds threshold, prunes that branch
bool DepthLimSearch(int initialState, int goalState, int depthLimit){
    if (initialState == goalState)
        return true;

    if(maxDepth <= 0)
        return false;

    for (int i = adjacencyList[initialState].begin(); i!= adjacencyList[initialState].end(); ++i)
        if (DepthLimSearch(*i, goalState, depthLimit -1 ) == true)
            return true;

    return false;
}

bool IDDDFS(int initialState, int goalState, int maxDepth){

    for i=initialState; i<=maxDepth ; i++){

        if (goalState > maxDepth)
            break; //A*
        if(dfs(initialState, goalState, i))
            return true;
    }
return false;

}
