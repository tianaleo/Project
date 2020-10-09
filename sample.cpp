#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

//may have to figure how to use all this things

class Node 
{
  long long key;
  string name;
  Node* left;
  Node* right;
  Node* parent;
public:
  Node()
  {
    key=-1;
    left=NULL;
    right=NULL;
    parent=NULL;
    name = "";
  }

  void setKey(long aKey)
  {
    key = aKey; 
  }

  void setLeft(Node* aLeft)
  {
    left = aLeft; 
  }

  void setRight(Node* aRight)
  {
    right = aRight; 
  }

  void setParent(Node* aParent)
  {
      parent=aParent;
  }
  
  void setName(string word)
  {
    name = word;
  }

  long long Key() 
  {
    return key; 
  }

  string Name()
  {
    return name; 
  }

  Node* Left()
  {
    return left; 
  }

  Node* Right()
  {
    return right; 
  }
  Node* Parent()
  {
      return parent;
  }

};

// Tree class
class Tree 
{
  Node* root;
public:
  Tree();
  Node* Root() { return root; };
  void addNode(long long key, string name);
  bool deleteNode(Node* root, long long key);
  Node* largest(Node* root);
  void print_inorder();
  void inorder(Node* root);
  void print_preorder(ofstream& output);
  void preorder(Node* root,int level,ofstream& output);
  void locate( long long d);
private:
  void addNode(long long key, Node* leaf, string name);
  bool dltNode(Node* root);
};

// Constructor
Tree::Tree() 
{
  root = NULL;
}


//Delete a node
bool Tree::deleteNode(Node* root, long long key)
{
  if(root == NULL)
    {
      return false;
    }
  else
    if(key < root->Key())
      {
	return deleteNode(root->Left(),key);
      }
    else if(key > root->Key())
      {
	return deleteNode(root->Right(),key);
      }
    else
      {
	return dltNode(root);
      }

}

bool Tree::dltNode(Node* root)
{
   if(root->Left() ==NULL && root->Right() == NULL)
    {
        if(root->Parent()->Left() == root)
        {
            root->Parent()->setLeft(NULL);
        }
        else if(root->Parent()->Right() == root)
        {
            root->Parent()->setRight(NULL);
        }
        
        delete root;
        return true;
    }
   else if (root->Left() == NULL)
    {
        
      Node* temp = root;
      root = root->Right();
      
      if(temp->Parent()->Left() == temp)
      {
          temp->Parent()->setLeft(root);
      }
      else if (temp->Parent()->Right() == temp)
      {
          temp->Parent()->setRight(root);
      }
      
      delete temp;
      return true;
    }
  else if (root->Left() != NULL && root->Right()==NULL)
    {
      Node* temp = root;
      root = root->Left();
      
      if(temp->Parent()->Left() == temp)
      {
          temp->Parent()->setLeft(root);
      }
      else if (temp->Parent()->Right() == temp)
      {
          temp->Parent()->setRight(root);
      }
      
      delete temp;
      return true;
    }
  else
    {
      Node* large = largest(root->Left());
      root->setKey(large->Key());
      root->setName(large->Name());
      return deleteNode(root->Left(),large->Key());
    }
}

Node* Tree::largest(Node* root)
{
  if(root->Right() == NULL)
    {
      return root;
    }
  else
    {
      return largest(root->Right());
    }
}


// Add a node
void Tree::addNode(long long key, string name) 
{
     // No elements. Add the root
  if ( root == NULL )
    {
      cout << "add root node: " << key << endl;
      Node* n = new Node();
      n->setKey(key);
      n->setName(name);
      root = n;
    }
  else
    {
      cout << "add other node: " << key << endl;
      addNode(key, root, name);
    }
}

// Add a node (private)
void Tree::addNode(long long key, Node* leaf, string name) 
{
  if ( key <= leaf->Key() )
    {
      if ( leaf->Left() != NULL )
	addNode(key, leaf->Left(), name);
      else
	{
          Node* n = new Node();
          n->setKey(key);
	      n->setName(name);
          leaf->setLeft(n);
          n->setParent(leaf);
	}
    }
  else 
    {
      if ( leaf->Right() != NULL )
	addNode(key, leaf->Right(), name);
      else
	{
          Node* n = new Node();
          n->setKey(key);
	  n->setName(name);
          leaf->setRight(n);
          n->setParent(leaf);
	}
    }
}



void Tree::print_preorder(ofstream& output)
{    
      
       preorder( root,0, output);
      
       
}

void Tree::preorder(Node* root,int level,ofstream& output)
{    
    
    if(root != NULL)
    {  for(int i=1;i <=level; i++)
      {
          output <<"   ";
      }
         output <<" "<<root->Key() <<" "<< root->Name() << endl; 
        if(root->Left()) preorder(root->Left(),level +1,output);
        if(root->Right()) preorder(root->Right(),level +1,output);
         
        
    }
    
    else return;
     
}
void Tree::print_inorder()
{    
      
       inorder(root);
      
       
}

void Tree::inorder(Node* root)
{    
    
    if(root != NULL)
    {
       
        if(root->Left()) inorder(root->Left());
         cout <<" "<<root->Key()<<" "<< root->Name() <<endl; 
        if(root->Right()) inorder(root->Right());
         
        
    }
    
    else return;
   
}



void Tree::locate( long long k)
{
    //Locate the element
    bool located = false;
    if(root == NULL)
    {
        cout<<" Empty tree "<<endl;
        return;
    }
    Node* curr;
   
    curr = root;
    while(curr != NULL)
    {
         if(curr->Key() == k)
         {
           located = true;
            cout << endl;
            cout <<"Data was found!" << endl;
            
         }
         else
         {
             //parent = curr;
             if(k > curr->Key()) curr = curr->Right();
             else curr = curr->Left();

         }
    }
    if(!located)
     {  cout << endl;
        cout<<" Data was not found! "<<endl;
        return;
    }

}




int main (void)
{
  Tree phone;
  char choice = 'e';

  long long number = 0;
  string words;
  
  
  while((choice != 'q') && (choice != 'Q'))
    {
      cout << "Enter the letter for the corresponding operation:"<<endl<<"A - add"<<endl<< "D - delete" 
	   << endl << "L - locate" << endl << "P - print" << endl << "Q - quit" <<endl<<endl;

      cin>> choice;
      
      if(choice == 'A'||choice == 'a')
	{
	  cout<<"Enter a phone number"<<endl;
	  cin>>number;
	  cout<<"Enter a name"<<endl;
	  cin>>words;

	  phone.addNode(number,words);      

	}
      else if(choice == 'D' || choice == 'd')
	{
	  cout<<"Enter a phone number to delete" << endl;
	  cin>>number;
	  phone.deleteNode(phone.Root(),number);
	}
      else if(choice == 'P' || choice == 'p')
	{
	  phone.print_inorder();
	}
    else if (choice == 'Q' || choice == 'q')
    {
        ofstream output("tree.dat");
        phone.print_preorder(output);
        output.close();
        
    }
    else if (choice == 'l' || choice == 'L')
    {
        cout<<"Enter phone number to locate"<<endl;
        cin>>number;
        phone.locate(number);
    }

      
    }



  return 0;
}

