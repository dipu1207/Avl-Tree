

# include<iomanip>
# include<iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
#include <bits/stdc++.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
class AVL_Node{ 
 private: 
  int key; 
 int bf; // balance factor bf = height(left subtree) – height(right subtree) 
 AVL_Node *LChild;
 AVL_Node *RChild; 

  public:
	
	AVL_Node(int k)
	{
		key=k;
		bf=0;
		LChild=NULL;
		RChild=NULL;
		
	}

 friend class AVL_Tree; 
 ~AVL_Node(){
 	delete LChild;
 	delete RChild;
 }

}; 

class AVL_Tree{ 
 private: 
 AVL_Node *root; 

public: 
 //constructor
 AVL_Tree(){
 	root =new AVL_Node(-1);
 	
 	 } 
 
 void AVL_Insert(int k); 
 void AVL_Delete(int k); 
 bool AVL_Search(int k); 
 void AVL_Print(); 
 
 ~AVL_Tree(){
 delete root;	
 } 
};
 

 void AVL_Tree::AVL_Insert(int key)
 {
       
	    
	    AVL_Node *temp=new AVL_Node(key);
	    AVL_Node *parImBal=root;//here parImBal points to parent of ImBal
       //ImBal points to node that can have imbalance and and ImBalChild is child of ImBal which help in rotation 
       AVL_Node* ImBal=root->RChild;
       AVL_Node* iterator=root->RChild; 
       AVL_Node* ImBalChild;
		 AVL_Node*q; 
		    
 	 if(iterator==NULL)//if tree has no element then we insert the first element and return
 	  {
 	   	root->RChild=temp;   
        
          return;
		}   
   
		
	    
	//this loop runs until we find the position to insert new node 
	while(true)
	 {    
	   	if(key<iterator->key)
	 	    
	 	  	q=iterator->LChild;
	 	  	 
	 	else if(key>iterator->key)
		  
		  	q=iterator->RChild;
		  
		else {
		  throw "Element already exists!!";
		  	
		    } 
		  
		if(q==NULL)  // iterator has reached the leaf 
		{ 
	        
	        break;
		}
		else if(q->bf!=0)   // here we will shift parImBal and ImBal
	 	  	 {  
	 	  	      parImBal=iterator;
	 	  	      ImBal=q;
	 	  	      
				}
	 	
	 	   iterator=q;   //iterator points to q
	 	 }//end while
	 
   // we have inserted new node at its correct position
		if(key<iterator->key)
	   {iterator->LChild=temp;
	   q=iterator->LChild;}
	else if(key>iterator->key)
	    {iterator->RChild=temp;
	    q=iterator->RChild;}

// now we will make a int variable a which will be -1 if insertion is done on right side of ImBal else it will be +1 if done  on left side of s
 int a;
 if(key<ImBal->key)
   a=1;
   else a=(-1);

	//now we will set the balance factor between ImBal and q
  
  if(a==1)
     {
     	ImBalChild=ImBal->LChild;
     	iterator=ImBal->LChild;
	 }
     
    else if(a==(-1)) {
    	ImBalChild=ImBal->RChild;
         iterator=ImBal->RChild;
	}

    
    // we will keep updating the balance factor of node from path q to ImBal and all those node has balance factor as 0 so we will either make them -1 or +1 
    while(iterator!=q) 
    {
       if(key< iterator->key)
	    {  iterator->bf=1;
	       iterator=iterator->LChild;
		  }  
		  else if(key> iterator->key) {
		  	iterator->bf=-1;
		  	iterator=iterator->RChild;
		  }
		  
	}
	// now we will balance the tree by checking if balancing is required or not
	 if(ImBal->bf==0) // if the balance factor of ImBal is 0 that means the height is increased by one depending on a value but there is no need of balancing 
	 {
	 	//set the new balance factor of ImBal= a
	 	ImBal->bf=a;
	 	return;
	 }
	 
	 else if(ImBal->bf==(-1*a))// means ImBalhas balance factor opposite to a means insertion will make ImBalbalance factor to 0
	  {
	  	ImBal->bf=0;
	  	return;
	  }
	  else 
	   {//here we will see two cases one is single rotation and one is double rotation
	      // for single rotatio we will use balance factor of r to check
	       if(ImBalChild->bf==a)
	       {
	       	// now to check if it is LL or RR we will use value of a, if it is -1 then RR else LL
	       	if(a==1)//LL rotation
			   {
			   	iterator=ImBalChild;
			   	ImBal->LChild=ImBalChild->RChild;
			   	ImBalChild->RChild=ImBal;
			   	ImBal->bf=0;
			   	ImBalChild->bf=0;
			   }
			   else if(a==-1){//RR rotation
			        iterator=ImBalChild;
			        ImBal->RChild=ImBalChild->LChild;
			        ImBalChild->LChild=ImBal;
			        ImBal->bf=0;
			        ImBalChild->bf=0;
			   }
		   }
		   //double rotation
		   else{
		   	     if(a==1)//LR rotation
		   	     {
		   	     	iterator=ImBalChild->RChild;
		   	     	ImBalChild->RChild=iterator->LChild;
						iterator->LChild=ImBalChild;
						ImBal->LChild=iterator->RChild;
						iterator->RChild=ImBal;
			       
		   	       if(iterator->bf==0)
		   	       { 
		   	             ImBal->bf=0;
					      ImBalChild->bf=0;
					  }
					 else if(iterator->bf==1)
					 {
					 	ImBal->bf=-1;
					 	ImBalChild->bf=0;
					  } 
					  else{
					  	ImBal->bf=0;
					  	ImBalChild->bf=1;
					  }
					}//LR end
		   	
		   	    else if(a==-1) //RL rotation
		   	    {
		   	    	iterator=ImBalChild->LChild;
		   	    	ImBalChild->LChild=iterator->RChild;
		   	    	iterator->RChild=ImBalChild;
		   	    	ImBal->RChild=iterator->LChild;
		   	    	iterator->LChild=ImBal;
				   if(iterator->bf==0)
		   	       { 
		   	         ImBal->bf=0;
					       ImBalChild->bf=0;
					  }
					 else if(iterator->bf==1)
					 {
					 	ImBal->bf=0;
					 	ImBalChild->bf=-1;
					  } 
					  else{
					  	ImBal->bf=1;
					  	ImBalChild->bf=0;
					  }
				   }//RL end
				   
		   }//end of inner else
	  }//end of else
		//after rotation set lchild and rhild of parent of s
    if(ImBal == parImBal->RChild) 
	   parImBal->RChild = iterator;
	else parImBal->LChild = iterator;
  }  
  //search the key
bool AVL_Tree::AVL_Search(int key)
{
	AVL_Node * searchptr=root->RChild;
	if(searchptr==NULL)
	   throw "tree is empty";
    while(searchptr!=NULL)
    {
    	if(key<searchptr->key)
    	  searchptr=searchptr->LChild;
    	else if(key>searchptr->key)
    	   searchptr=searchptr->RChild;
    	else return true;
	}
	return false;//search unsuccessful
	
}
    
void AVL_Tree::AVL_Delete(int key){
    
    //to check if key is present or not
    int check = AVL_Search(key);
    if(check==0)
      {
        cout<< " key not present please enter a valid key"<<endl;
         return;
         }
    
    AVL_Node *itrPoint = root->RChild; 
    
    // ImBal -> AVL_Node to be balanced
    // parImBal -> parent of the AVL_Node to be balanced
    // ImBalChild -> LChild/RChild child of the AVL_Node to be balanced
    AVL_Node *ImBal, *parImBal, *ImBalChild;
    
    stack<AVL_Node*> walkStack; // saves the path to the AVL_Node
    walkStack.push(root); //pushing the head (dummy) AVL_Node

    while(itrPoint){
        if(key < itrPoint->key){
            walkStack.push(itrPoint);
            itrPoint = itrPoint->LChild;
        }
        else if(key > itrPoint->key){
            walkStack.push(itrPoint);
            itrPoint = itrPoint->RChild;
        }
        else
            break;
    }
    
    // if itrPoint is leaf
      if(itrPoint->LChild==NULL && itrPoint->RChild==NULL)
        {
           AVL_Node*par=walkStack.top();
           if(itrPoint==par->LChild)
            par->LChild=NULL;
            else 
             par->RChild=NULL;
             delete itrPoint;
        }
       

        // if itrPoint has a single child 
       else if(!itrPoint->LChild || !itrPoint->RChild)
       {
            AVL_Node *temp = itrPoint->LChild ? itrPoint->LChild : itrPoint->RChild;
           

            
                itrPoint->key = temp->key;
                itrPoint->bf = temp->bf;
                itrPoint->LChild = temp->LChild;
                itrPoint->RChild = temp->RChild;
                delete temp;
        }

        // AVL_Node to be deleted has both the children
        else{
            walkStack.push(itrPoint);
            AVL_Node *succ = itrPoint->RChild; //finding the successor of itrPoint
            while(succ->LChild){
                walkStack.push(succ);
                succ = succ->LChild;
            }
            itrPoint->key = succ->key;
            key = succ->key; // because the AVL_Node that is being deleted is the successor
            AVL_Node *temp = succ->LChild ? succ->LChild : succ->RChild;
            AVL_Node *par = walkStack.top();

            if(!temp){
                temp = succ;
                if(succ == par->LChild)
                    par->LChild = NULL;
                else par->RChild = NULL;
                succ = NULL;
            }
            else{
                succ->key = temp->key;
                succ->bf = temp->bf;
                succ->LChild = temp->LChild;
                succ->RChild = temp->RChild;
            }
            delete temp;
        }
    


   
    while(walkStack.top() != root){
        ImBal = walkStack.top();
        int a = key < ImBal->key ? 1 : -1;
        walkStack.pop();
        parImBal = walkStack.top();
    
        if(ImBal->bf == a)
        {  // here the node balanced had one more height on same side on which deletion happend so it got balanced
            ImBal->bf = 0;
            continue;
        }
        else if(ImBal->bf == 0)
        {
            //here node to be balanced was previously balanced to 0 but now its balance factor will be negative to the side the deletion occured
            ImBal->bf = -1*a;
            return;//no further balancing required
        }
        else{
             //here node to be balanced was having a imbalance of 1 but now we deleted element on the side where it was already tilted so we made an 
			 //imbalance of 2 and now we will do rotations
            if(ImBal->bf==1)
              ImBalChild=ImBal->LChild;
              else 
              ImBalChild=ImBal->RChild;
            //single rotation
            if(ImBalChild->bf == -1*a){
                if(a == -1){
                    itrPoint = ImBalChild;
                    ImBal->LChild = ImBalChild->RChild;
                    ImBalChild->RChild = ImBal;
                    ImBal->bf = 0;
                    ImBalChild->bf = 0; 
                }
                else if(a == 1){
                    itrPoint = ImBalChild;
                    ImBal->RChild = ImBalChild->LChild;
                    ImBalChild->LChild = ImBal;
                    ImBal->bf = 0;
                    ImBalChild->bf = 0;
                }
            }
            //single rotation
            else if(ImBalChild->bf == 0){
                if(a == -1){
                    itrPoint = ImBalChild;
                    ImBal->LChild = ImBalChild->RChild;
                    ImBalChild->RChild = ImBal;
                    ImBalChild->bf = a; 
                }
                else if(a == 1){
                    itrPoint = ImBalChild;
                    ImBal->RChild = ImBalChild->LChild;
                    ImBalChild->LChild = ImBal;
                    ImBalChild->bf = a;
                }
            }
            //double rotation
            else if(ImBalChild->bf == a){
                if(a == -1){
                    itrPoint = ImBalChild->RChild;
                    ImBalChild->RChild = itrPoint->LChild;
                    itrPoint->LChild = ImBalChild;
                    ImBal->LChild = itrPoint->RChild;
                    itrPoint->RChild = ImBal;
                    
				//	ImBal->bf = itrPoint->bf == 0 ? 0 : itrPoint->bf == 1 ? -1 : 0;
                    //ImBalChild->bf = itrPoint->bf == 0 ? 0 : itrPoint->bf == 1 ? 0 : 1;
                  //  itrPoint->bf = 0;
                    
                    if(itrPoint->bf==0)
                    {
                        ImBal->bf=0;
						ImBalChild->bf=0;	
					}
					else if(itrPoint->bf==1)
					   {
					      ImBal->bf=-1;
						ImBalChild->bf=0;	
				
					   }
					 else{
							ImBal->bf=0;
						ImBalChild->bf=1;	
				
				        }
				itrPoint->bf=0;	     
					
                    
                }
                else if(a == 1){
                    itrPoint = ImBalChild->LChild;
                    ImBalChild->LChild = itrPoint->RChild;
                    itrPoint->RChild = ImBalChild;
                    ImBal->RChild = itrPoint->LChild;
                    itrPoint->LChild = ImBal;
                   // ImBal->bf = itrPoint->bf == 0 ? 0 : itrPoint->bf == 1 ? 0 : 1;
                    //ImBalChild->bf = itrPoint->bf == 0 ? 0 : itrPoint->bf == 1 ? -1 : 0;
                    //itrPoint->bf = 0;
                     if(itrPoint->bf==0)
                    {
                        ImBal->bf=0;
						ImBalChild->bf=0;	
					}
					else if(itrPoint->bf==1)
					   {
					      ImBal->bf=0;
						ImBalChild->bf=-1;	
				
					   }
					 else{
							ImBal->bf=1;
						ImBalChild->bf=0;	
				
				        }
					     itrPoint->bf=0;
					
                  
                }
            }
        }
        if(ImBal == parImBal->RChild) parImBal->RChild = itrPoint;
        else parImBal->LChild = itrPoint;       
    }

  }



void AVL_Tree::AVL_Print()
{
	
 queue<AVL_Node*> queue;
 string nodeStructure = "";
 string linkStructure = "";
 ofstream graphViz;

 //string treeFileName = "graphVizFile.gv";
  graphViz.open("graphVizFile.gv");

 if (root->RChild == NULL)
{
graphViz << "digraph G {" << endl;
graphViz << "node [shape = record, height = .1];" << endl;
graphViz << "}" << endl;
graphViz.close();

return;
}

 queue.push(root->RChild);
 
while (!queue.empty())
{
  AVL_Node * currNode=queue.front(); 
  queue.pop();
if(currNode->LChild != NULL)
  queue.push(currNode->LChild);
if (currNode->RChild != NULL)
  queue.push(currNode->RChild);
 nodeStructure.append(to_string(currNode->key));
 nodeStructure.append("[label = \"<L> |<D> ");
 nodeStructure.append(to_string(currNode->key));
 nodeStructure.append("|<bf>");
 nodeStructure.append(to_string(currNode->bf));
 nodeStructure.append("|<R> \"];\n");
 if (currNode->LChild != NULL)
  {
	linkStructure.append("\"");
	linkStructure.append(to_string(currNode->key));
	linkStructure.append("\":L -> \"");
	linkStructure.append(to_string(currNode->LChild->key));
	linkStructure.append("\":D");

	linkStructure.append(";\n");
	}
 if (currNode->RChild != NULL)
   {
	linkStructure.append("\"");
	linkStructure.append(to_string(currNode->key));
	linkStructure.append("\":R -> \"");
	linkStructure.append(to_string(currNode->RChild->key));
	linkStructure.append("\":D");

	linkStructure.append(";\n");
   }
}//end while
graphViz << "digraph G {" << endl;
graphViz << "node [shape = record, height = .1];" << endl;
 graphViz << nodeStructure;
 graphViz << linkStructure;
 graphViz << "}" << endl;
 graphViz.close();

}



int main(int argc, char** argv) {
  AVL_Tree obj;
  int key,choice,x;
  while(1)
  {
   cout<<"enter your choices"<<endl;
   cout<<"1.insert in avl tree"<<endl;
   cout<<"2.search an element"<<endl;
   cout<<"3.delete an element"<<endl;
   cout<<"4.print tree"<<endl;	
   	cout<<"5.exit "<<endl;	
  	
  	
  	cin>>choice;
  	switch(choice)
  	{
  		case 1: cout<<"enter key to be inserted"<<endl;
  		         cin>>key;
  		         obj.AVL_Insert(key);
  		         break;
  	   case 2: cout<<"enter key to search"<<endl;
  	            cin>>key;
  	          x=obj.AVL_Search(key);
  	            if(x==1)
  	             cout<<"search success"<<endl;
  	             else 
  	             cout<<"search unsuccess"<<endl;
  	              break;
  		case 3:cout<<"enter key to delete"<<endl;
  		        cin>>key;
  		        obj.AVL_Delete(key);
  		        break;
  		case 4: obj.AVL_Print();
  		         break;
         
		  case 5: exit(0) ;
		            
  		default: cout<<"invalid input please try again" <<endl;
	  }
  }
	return 0;
	
}
