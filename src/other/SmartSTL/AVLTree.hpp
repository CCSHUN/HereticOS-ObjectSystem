///////////////////////////////////////////////////////////////////////////////////
//	Copyright 2017 shushen,ye
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//	http://www.apache.org/licenses/LICENSE-2.0
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
///////////////////////////////////////////////////////////////////////////////////

/*Completely describe one of the following algorithms, including  
 initialization,  
 searching,  
 insertion,  
 deletion  
 operations  
AVL tree  
Red-Black tree  
*/   
//AVL tree;   
#include<iostream>   
#include<string>   
#include<vector>   
#include<queue>   
using namespace std;   
template<class T>   
struct Node{   
    T key;   
    int pf;   
    Node *left;   
    Node *right;   
    Node(T val,int =0,Node* =0,Node* =0);   
};   
template<class T>   
Node<T>::Node(T val,int opf=0,Node<T>* oleft=0,Node<T>* oright=0):key(val),pf(opf),left(oleft),right(oright){   
}   
template<class T>   
struct Tree{   
    Node<T>* Root;   
    Tree();   
    Tree(T* iodr,T* lodr,int =0);//用inorder 和lever order建立一棵树   
    Tree(T* Array,int =0);   
    void Insert(T el);   
    void Insert(T * Array,int =0);   
    void Delete(T el);   
    int Find(T tel);   
    int Find(T el,vector<Node<T>*>& vec_node,string & drt);   
    void Rt_RR();   
    void Rt_LR();   
};   
template<class T>   
Tree<T>::Tree():Root(0){   
}   
template<class T>   
Tree<T>::Tree(T* iodr,T* lodr,int size):Root(NULL){   
    //iodr=g d h b e i a f j c   
    //level_order=a b c d e f g h i j   
    if(size==0) return;   
       
}   
template<class T>   
Tree<T>::Tree(T* Array,int size):Root(0){   
    if(size==0) return;   
    for(int i=0;i<size;i++){   
        this->Insert(Array[i]);   
    }   
}   
template<class T>   
void Tree<T>::Insert(T *Array,int size){   
    if(size==0) return;   
    for(int i=0;i<size;i++){   
        this->Insert(Array[i]);   
    }   
}   
template<class T>   
void Tree<T>::Insert(T el){   
    vector< Node<T>* > path;   
    if(Root==NULL){   
        Root=new Node<T>(el,0,0,0);   
        return;   
    }   
    Node<T>* temp=Root;   
    string drt;   
    for(;;){   
        if(el>temp->key){//插在这个结点的右边   
            if(temp->right==NULL){   
                temp->right=new Node<T>(el,0,0,0);    
                path.push_back(temp);   
                path.push_back(temp->right);   
                drt.push_back('R');break;   
            }   
            else{   
                path.push_back(temp);   
                temp=temp->right;   
                drt.push_back('R');   
            }   
        }   
        else{   
            if(el<temp->key){//插在这个结点的左边   
                if(temp->left==NULL){   
                    temp->left=new Node<T>(el,0,0,0);   
                    path.push_back(temp);   
                    path.push_back(temp->left);   
                    drt.push_back('L');break;   
                }   
                else{   
                    path.push_back(temp);   
                    drt.push_back('L');   
                    temp=temp->left;   
                }   
            }   
            else   
                return;//这个元素和某个元素相等,所以不予加入.   
        }   
    }   
    vector<bool>Longer(path.size(),0);   
    bool Nd_Rt=false;   
    int Brk_pt;   
    {   
        int j=(int)path.size()-1;//最后一个点   
         Longer[j]=1;   
           
    }   
    for(int i=(int)path.size()-2;i>=0;i--){   
        int temp=path[i]->pf;   
        if(Longer[i+1]){//以这个点为根点的子结树变长了.   
            if(temp==0) Longer[i]=1;   
            if(drt[i]=='R'){//从右边   
                path[i]->pf=temp-1;   
                if(path[i]->pf==-2){   
                    Nd_Rt=true;   
                    Brk_pt=i; break;   
                }   
            }   
            else{//从左边   
                path[i]->pf=temp+1;   
                if(path[i]->pf==2){   
                    Nd_Rt=true;    
                    Brk_pt=i; break;   
                }   
            }   
        }   
        else{//这个结点的深度不变,所以不用再往上找了   
            break;   
        }   
    }   
    if(!Nd_Rt) return;   
    //发现了一个   
    //cout<<drt<<endl;   
    string Temp;   
    Temp.assign(drt.begin()+Brk_pt,drt.begin()+Brk_pt+2);//Brk_pt的位置为第一个为二的位置   
    //cout<<"Temp:    "<<Temp<<endl;   
    if(Temp=="LL"){//LL的情况   
        Node<T>* parent=path[Brk_pt];     //Node<T>* ch=parent->left;   
        parent->pf=0; parent->left->pf=0;   
        if(parent!=Root){   
            RR<T>(path[Brk_pt-1],parent);    
        }   
        else{//此时要对parent进得RR操作   
            Rt_RR();   
        }   
        return;   
    }   
    if(Temp=="RR"){//RR的情况   
        Node<T>* parent=path[Brk_pt];   
        parent->pf=0; parent->right->pf=0;   
        if(parent!=Root){   
            LR<T>(path[Brk_pt-1],parent);   
        }   
        else{   
            Rt_LR();   
        }   
        return;   
    }   
    if(Temp=="LR"){//LR的情况   
        int key=path[Brk_pt+2]->pf;   
        switch(key){   
            case 0:   
                path[Brk_pt]->pf=0; path[Brk_pt+1]->pf=0;path[Brk_pt+2]->pf=0;   
                 break;   
            case 1:   
                path[Brk_pt]->pf=-1; path[Brk_pt+1]->pf=0;path[Brk_pt+2]->pf=0;   
                  break;   
            case -1:   
                path[Brk_pt]->pf=0; path[Brk_pt+1]->pf=1; path[Brk_pt+2]->pf=0;   
                    break;   
        }   
        LR<T>(path[Brk_pt],path[Brk_pt+1]);   
        if(path[Brk_pt]==Root){   
                Rt_RR();   
        }   
        else{   
            RR<T>(path[Brk_pt-1],path[Brk_pt]);   
        }   
        return;   
    }   
    if(Temp=="RL"){//RL的情况   
        path[Brk_pt]->pf=0;path[Brk_pt+1]->pf=0;   
        RR<T>(path[Brk_pt],path[Brk_pt+1]);   
        if(path[Brk_pt]==Root){   
            Rt_LR();   
        }   
        else{   
            LR<T>(path[Brk_pt-1],path[Brk_pt]);   
        }   
        return;   
    }   
}   
template<class T>   
void Tree<T>::Delete(T el){   
    vector<Node<T>*> path;   
    string drt;   
    if(!Find(el,path,drt)){   
        cout<<"the element that you want to delete from the tree is not found"<<endl;   
        return;   
    }   
    if(path[path.size()-1]->left!=NULL||path[path.size()-1]->right!=NULL){   
        cout<<"deletion failed because the node upon which the element hang is not a leaf"<<endl;   
        return;    
    }   
    cout<<"Have already deleted element on level "<<drt.size()<<endl;   
    if(path.size()==1){//只有一个根;   
        delete Root;   
        Root=NULL;   
        return;   
    }   
    int dl_pst;//delete position: from which a subtree is decreased;   
    delete path[path.size()-1];   
    if(drt[drt.size()-1]=='R'){   
        path[path.size()-2]->right=NULL;   
    }   
    else{   
        path[path.size()-2]->left=NULL;   
    }   
    dl_pst=(int)path.size()-2;   
    while(dl_pst>=0){   
        if(drt[dl_pst]=='R'){//dl_pst所在的位置的pf值   
            path[dl_pst]->pf++;   
        }   
        else{   
            path[dl_pst]->pf--;   
        }   
        if(path[dl_pst]->pf==-1||path[dl_pst]->pf==1){//=> no change in height of subtree rooted at q.   
            return;   
        }   
        if(path[dl_pst]->pf==0){//=> height of subtree rooted at q has decreased by 1.   
            dl_pst--;   
            continue;   
        }   
        //=> tree is unbalanced at q   
        if(path[dl_pst]->pf==2){//从右边删掉   
            int key=path[dl_pst]->left->pf;   
            switch( key){   
                case 0://R0   
                    path[dl_pst]->pf=1;   
                    path[dl_pst]->left->pf=-1;   
                    if(dl_pst==0){   
                        Rt_RR();   
                    }   
                    else{   
                        RR<T>(path[dl_pst-1],path[dl_pst]);   
                    }   
                    return ;   
                case 1://R1   
                    path[dl_pst]->pf=0;   
                    path[dl_pst]->left->pf=0;   
                    if(dl_pst==0){   
                        Rt_RR();   
                    }   
                    else{   
                        RR<T>(path[dl_pst-1],path[dl_pst]);   
                    }   
                    dl_pst--;break;   
                case -1://R-1   
                    Node<T>* A=path[dl_pst];Node<T>*B;Node<T>*C;   
                    B=A->left;C=B->right;   
                    switch(C->pf){   
                case 0:B->pf=0;A->pf=0; break;   
                case 1:B->pf=0;A->pf=-1; break;   
                case -1:B->pf=1;A->pf=0; break;   
                    }   
                    C->pf=0;   
                    LR<T>(A,B);   
                    if(A==Root){   
                        Rt_RR();   
                    }   
                    else{   
                        RR<T>(path[dl_pst-1],path[dl_pst]);   
                    }   
                    dl_pst--;break;   
   
            }//switch key;   
            continue;   
        }//从右边删掉   
        if(path[dl_pst]->pf==-2){// 从左边删掉   
            int key=path[dl_pst]->right->pf;   
            switch( key){   
                case 0://L0   
                    path[dl_pst]->pf=-1;   
                    path[dl_pst]->right->pf=1;   
                    if(dl_pst==0){   
                        Rt_LR();   
                    }   
                    else{   
                        LR<T>(path[dl_pst-1],path[dl_pst]);   
                    }   
                    return ;   
                case -1://L-1   
                    path[dl_pst]->pf=0;   
                    path[dl_pst]->right->pf=0;   
                    if(dl_pst==0){   
                        Rt_LR();   
                    }   
                    else{   
                        LR<T>(path[dl_pst-1],path[dl_pst]);   
                    }   
                    dl_pst--;break;   
                case 1://L1   
                    Node<T>* A=path[dl_pst];Node<T>*B;Node<T>*C;   
                    B=A->right;C=B->left;   
                    switch(C->pf){   
                case 0:B->pf=0;A->pf=0; break;   
                case 1:B->pf=-1;A->pf=0; break;   
                case -1:B->pf=0;A->pf=1; break;   
                    }   
                    C->pf=0;   
                    RR<T>(A,B);   
                    if(A==Root){   
                        Rt_RR();   
                    }   
                    else{   
                        RR<T>(path[dl_pst-1],path[dl_pst]);   
                    }   
                    dl_pst--;break;   
   
            }//switch key;L0,L1,L-1;   
            continue;   
        }//从左边删掉   
    }//while dl_pst>=0;   
}   
template<class T>   
int  Tree<T>::Find(T el,vector<Node<T>*>& vec_node,string & drt){   
    Node<T>* p=Root;   
    while(p!=NULL){   
        if(el>p->key){   
            vec_node.push_back(p);   
            drt.push_back('R');   
            p=p->right;   
        }   
        else{   
            if(el<p->key){   
                vec_node.push_back(p);   
                drt.push_back('L');   
                p=p->left;   
            }   
            else{//P等于key   
                vec_node.push_back(p);   
                return true;   
            }   
        }   
    }   
    return false;   
}   
template<class T>   
int Tree<T>::Find(T el){   
    vector<Node<T>* > tmp_vec;   
    string tmp_drt;   
    if(Find(el,tmp_vec,tmp_drt)){   
        cout<<"ele found on level "<<tmp_drt.size()<<endl;   
        return true;   
    }   
    else{   
        cout<<"ele not found"<<endl;   
        return false;   
    }   
           
}   
template<class T>   
void Tree<T>::Rt_RR(){   
    Node<T>* temp=Root;   
    Root=Root->left;   
    temp->left=Root->right;   
    Root->right=temp;   
    return;   
}   
template<class T>   
void Tree<T>::Rt_LR(){   
    Node<T>* temp=Root;   
    Root=Root->right;   
    temp->right=Root->left;   
    Root->left=temp;   
    return;   
}   
template<class T>   
void RR(Node<T>* grd,Node<T>* par){//不能par为根结点的情况.   
    Node<T>* ch=par->left;   
    Node<T>* temp=ch->right;   
    if(par==grd->right){   
        grd->right=ch;   
    }   
    else{   
        if(par==grd->left){   
            grd->left=ch;   
        }   
    }   
    ch->right=par;   
    par->left=temp;   
   
    return;    
}   
template<class T>   
void LR(Node<T>* grd,Node<T>* par){   
    Node<T> * ch=par->right;   
    Node<T>* temp=ch->left;   
    if(par==grd->right){   
        grd->right=ch;   
    }   
    else{   
        if(par==grd->left){   
            grd->left=ch;   
        }   
    }   
    ch->left=par;   
    par->right=temp;   
    return;   
}   
template<class T,class func>   
void Traverse(Tree<T> &tr,func Visit){   
    typename Node<T>* Rt;   
    Rt=tr.Root;   
    if(Rt==NULL) return;   
    queue< Node<T>* > trqueue;   
    trqueue.push(Rt);   
    while(!trqueue.empty()){   
        Rt=trqueue.front();   
        trqueue.pop();   
        (*Visit)(Rt);   
        if(Rt->left!=0){   
            trqueue.push(Rt->left);   
        }   
        if(Rt->right!=0){   
            trqueue.push(Rt->right);   
        }   
    }   
    return;   
}   
template<class T>   
void Print(Node<T>* para){   
    cout<<para->key<<' ';   
    return;   
}   
template<class T>   
void Getpf(Node<T>* para){   
    cout<<para->pf<<' ';   
    return;   
}   
const int N=14;   
int TestAVL(){   
       
    int Data[]={5,6,7,4,123,0,155};   
    int Data2[]={10,40,45,60,7,8,9,30,20,35,25,3,5,1};   
    int tempdata[]={10,40,45,60,7,8,9,30};   
    Tree<int> test(Data2,14);   
    //test.Insert(tempdata,8);//initialization   
    Traverse<int,void(*)( Node<int>*  )>(test,Print<int>);cout<<endl;//Traverse_输出各点的值   
    Traverse<int,void(*)(Node<int>*)>(test,Getpf<int>);cout<<endl;//Traverse_输出各点的PF值   
    for(int i=0;i<14;i++){//searching   
        cout<<Data2[i]<<':';   
        test.Find(Data2[i]);   
    }   
    test.Delete(5);//deletion_only successful when the deletion is operated upon a leaf;   
    test.Delete(35);//delete 35;   
    Traverse<int,void(*)( Node<int>*  )>(test,Print<int>);cout<<endl;//Traverse_输出各点的值   
    return 0;   
}   