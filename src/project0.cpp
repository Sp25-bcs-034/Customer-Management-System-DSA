#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
using namespace std;

struct Node {
    string customerId;
    string firstName;
    string lastName;
    string company;
    string city;
    string country;
    string subscriptionDate;
    Node* next;
    Node* prev;
    Node(string customerId, string firstName, string lastName,string company, string city, string country, string subscriptionDate){
    this-> customerId = customerId;
     this ->firstName = firstName;
    this -> lastName = lastName;
    this -> company = company;
    this ->city = city;
    this -> country = country;
    this -> subscriptionDate = subscriptionDate;
    this -> next = NULL;
    this ->prev = NULL;
    }
};

Node* head = NULL;
Node* tail = NULL;
void addNode(string customerId, string firstName, string lastName,string company, string city, string country, string subscriptionDate){
   Node* newNode = new Node(customerId,firstName,lastName,company,city,country,subscriptionDate);
    if(head == NULL){
        head = tail = newNode;
        return;
    }
    tail -> next = newNode;
    newNode -> prev = tail;
    tail = newNode;
     
}

void printAll(){
   if(head == NULL){
    cout<<"Linked List is empty"<<endl;
    return;
   }
   Node* temp = head;
   while(temp != NULL){
    cout << "  Customer ID   : " << temp->customerId << endl;
    cout << "  Name          : " <<temp-> firstName << " " <<temp-> lastName << endl;
    cout << "  Company       : " << temp->company << endl;
    cout << "  City          : " << temp->city << endl;
    cout << "  Country       : " << temp->country << endl;
    cout << "  Subscribed On : " <<temp-> subscriptionDate << endl; 
   temp = temp -> next;
   }
} 
void reversePrint(){
    Node* temp = tail;
    while(temp != NULL){
    cout << "  Customer ID   : " << temp->customerId << endl;
    cout << "  Name          : " <<temp-> firstName << " " <<temp-> lastName << endl;
    cout << "  Company       : " << temp->company << endl;
    cout << "  City          : " << temp->city << endl;
    cout << "  Country       : " << temp->country << endl;
    cout << "  Subscribed On : " <<temp-> subscriptionDate << endl;         
temp = temp -> prev;
    }
}
    Node* search_by_name (string name ){
        Node* temp = head; 
        while (temp!=NULL){
            if ( temp->firstName == name || temp->lastName == name){
                return temp;
            }else {
                temp= temp->next;
            }
        }
        return NULL;
    }
    int countbyCountry(string country ){
        Node* temp  =head ;
        int count =0;
        while (temp!=NULL){
            if ( temp->country == country){
                count++;
            }
            temp = temp->next;
        }
        return count;
    } 
    
struct StackQueueNode{
    public:
    Node* data;
    StackQueueNode* next;
    StackQueueNode(){
        data = NULL;
        next = NULL;
    }
};
//Undo Deletion Log
struct Stack{   
    StackQueueNode* top;
    Stack(){
        top = NULL;
    }//push
    void saveDeletedCustomer(Node* customer){
        StackQueueNode* sn = new StackQueueNode;
        sn -> data = customer;
        sn -> next = top;
        top = sn;
    } //pop
    void removeFromUndoLog(){
        if(top == NULL){
            cout<<"Stack is Empty"<<endl;
            return;
        }
        StackQueueNode* temp = top;
        if(top -> next == NULL){
            top = NULL;
            delete temp;
        }
        else{
        top = top -> next;
        delete temp;
        }
    }//undo delete
    void undoLastDeletion(){
        if(top == NULL){
            cout<<"Nothing is deleted"<<endl;
            return;
        }
        Node* value = top -> data;
        addNode(value->customerId,value->firstName,value->lastName,value->company,value->city,value->country,value->subscriptionDate);
        delete value; 
        removeFromUndoLog(); //pop
        cout<<"Customer restored successfully"<<endl;
    }
    //printing
    void displayUndoLog(){
        StackQueueNode* temp = top;
        while(temp != NULL){
           cout << "  Customer ID   : " << temp->data->customerId << endl;
    cout << "  Name          : " <<temp-> data->firstName << " " <<temp-> data->lastName << endl;
    cout << "  Company       : " << temp->data->company << endl;
    cout << "  City          : " << temp->data->city << endl;
    cout << "  Country       : " << temp->data->country << endl;
    cout << "  Subscribed On : " <<temp->data-> subscriptionDate << endl;  
           temp = temp -> next;
        }
    }
    //stack size
     int  getUndoLogSize(){
        int count =0;
           StackQueueNode* temp = top;
           while (temp!=NULL){
            count++;
            temp= temp->next ;
           }
           return count;
     }
};
Stack s1;
   void deleteByCountry(string country){
    Node* temp = head;
    while(temp != NULL){
        Node* nextNode = temp->next;
        if(temp ->country == country){
            Node* copy = new Node(temp->customerId, temp->firstName, temp->lastName,temp->company, temp->city, temp->country,temp->subscriptionDate);
            if(temp -> prev == NULL && temp -> next == NULL){
                head = tail = NULL;
            }
            else if(temp->prev == NULL){
                    head = temp->next;
                    head->prev = NULL;
            }
            else if(temp -> next == NULL){
                tail = temp -> prev;
                tail -> next = NULL;
            }
            else{
            temp -> prev -> next = temp -> next;
            temp -> next -> prev = temp -> prev;
        }
         s1.saveDeletedCustomer(copy);
            delete temp;               
            temp = nextNode;
        }
        else{
            temp = temp -> next;   
        }
    
    }
}
struct Queue{
    StackQueueNode* rear;
    StackQueueNode* front;
    Queue(){
        rear = NULL;
        front = NULL;
    }
    void enqueue(Node* customer){
        StackQueueNode* sn = new StackQueueNode;
            sn -> data = customer;
            if(front == NULL){
                front = sn;
                rear = sn;
            }
            else{
            rear -> next = sn;
            rear = sn;
            }
    }
    void dequeue(){
        if(front == NULL){
        cout << "Queue is Empty" << endl;
        return;
       }
      StackQueueNode* temp = front;
      if(front == rear){
        front = rear = NULL;
      }
      else{
      front = front -> next;
      }
      delete temp;
    }
    void displayByQueue(){
        if(front == NULL){
            cout << "Queue is Empty" << endl;
            return;
        }
        StackQueueNode* temp = front;
         while(temp != NULL){
          cout << "  Customer ID   : " << temp->data->customerId << endl;
    cout << "  Name          : " <<temp-> data->firstName << " " <<temp-> data->lastName << endl;
    cout << "  Company       : " << temp->data->company << endl;
    cout << "  City          : " << temp->data->city << endl;
    cout << "  Country       : " << temp->data->country << endl;
    cout << "  Subscribed On : " <<temp->data-> subscriptionDate << endl;    
          temp = temp -> next;
         }
    } 
};
struct TreeNode {
    Node* data;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode( Node* customer){
        data = customer;
        left = NULL;
        right = NULL;
        height = 1;
    }
};
struct bst {
    bst (){
    };
     void insert (TreeNode* &root , Node* customer){
        if (root ==NULL){
            root = new TreeNode(customer);
        }else if (customer->customerId < root->data->customerId){
            insert(root->left,customer);
        }else if (customer->customerId > root->data->customerId){
            insert(root->right,customer);   
        }else{
            cout<<"Customer with ID "<<customer->customerId<<" already exists in the BST."<<endl;
     }  
}
void search (TreeNode* root, string customerId){
    if(root == NULL){
        cout<<"Customer with ID "<<customerId<<" not found in the BST."<<endl;
        return;
    }
    if(root ->data->customerId == customerId){
           cout << "  Customer ID   : " << root->data->customerId << endl;
    cout << "  Name          : " <<root-> data->firstName << " " <<root-> data->lastName << endl;
    cout << "  Company       : " << root->data->company << endl;
    cout << "  City          : " << root->data->city << endl;
    cout << "  Country       : " << root->data->country << endl;
    cout << "  Subscribed On : " <<root->data-> subscriptionDate << endl;  
       return;
    }
    if(customerId < root->data->customerId){
        search(root->left, customerId);
    }else{
        search(root->right, customerId);
    }
}
void inorder(TreeNode* root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    cout << "  Customer ID   : " << root->data->customerId << endl;
    cout << "  Name          : " <<root-> data->firstName << " " <<root-> data->lastName << endl;
    cout << "  Company       : " << root->data->company << endl;
    cout << "  City          : " << root->data->city << endl;
    cout << "  Country       : " << root->data->country << endl;
    cout << "  Subscribed On : " <<root->data-> subscriptionDate << endl;  
    inorder(root->right);

}
void buildbst(TreeNode* &root){
    Node* temp = head;
    while(temp != NULL){
        insert(root , temp);
        temp = temp->next;
    }
}
TreeNode* inordersuccessor (TreeNode* root){
    TreeNode* current = root ; 
    while ( current != NULL && current->left != NULL){
        current = current -> left;
}return current;
}

void deleteBST(TreeNode* &root , string customerid){
    if (root == NULL){
        cout<<"Customer with ID "<<customerid<<" not found in the BST."<<endl;
        return;
    }
    else {
        if (customerid < root->data->customerId){
            deleteBST(root->left, customerid);
    }else if (customerid > root->data->customerId){
        deleteBST(root->right, customerid);
    }else{
        if (root->left == NULL && root->right == NULL){
            delete root;
            root = NULL;
    } else if (root->left==NULL){
        TreeNode* temp =root;
        root = root->right;
        delete temp;

    }else if (root->right ==NULL){
    TreeNode* temp=root;
    root= root->left ;
    delete temp;
    }
    else {
        TreeNode* temp =inordersuccessor(root->right);
        root->data = temp->data;
        deleteBST(root->right, temp->data->customerId);
    }
}
    }
} 
};
class AVLTree {
public:
   AVLTree(){

   }
    int height(TreeNode* n) {
        if (n == NULL){
             return 0;
        }
        return n->height;
    }
    int getBalance(TreeNode* n) {
        if (n == NULL) {
            return 0;
        }
        return height(n->left) - height(n->right);
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }
   TreeNode* insertAVL(TreeNode* node,Node* customer) {
        if (node == NULL){
            return new TreeNode(customer);
        }

        if (customer -> customerId < node->data -> customerId){
            node->left = insertAVL(node->left, customer);
        }
        else if (customer -> customerId > node->data -> customerId){
            node->right = insertAVL(node->right, customer);
        }
        else{
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && customer -> customerId < node->left->data -> customerId){
            return rightRotate(node);
        }
        
        if (balance < -1 && customer-> customerId > node->right->data -> customerId){
            return leftRotate(node);
        }

        if (balance > 1 && customer-> customerId > node->left->data -> customerId) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && customer -> customerId < node->right->data -> customerId) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
     void inorder(TreeNode* root) {
        if (root != NULL) {
            inorder(root->left);
                cout << "  Customer ID   : " << root->data->customerId << endl;
    cout << "  Name          : " <<root-> data->firstName << " " <<root-> data->lastName << endl;
    cout << "  Company       : " << root->data->company << endl;
    cout << "  City          : " << root->data->city << endl;
    cout << "  Country       : " << root->data->country << endl;
    cout << "  Subscribed On : " <<root->data-> subscriptionDate << endl; 
            inorder(root->right);
        }
    }
      //  buildavl  
    void buildBalanceIndex(TreeNode* &root){
    Node* temp = head;
    while(temp != NULL){
        root = insertAVL(root , temp);
        temp = temp->next;  
    }
    }
    //searchByCustomerid
    void SearchBalanceIndex(TreeNode* root , string customerId){
        if(root == NULL){
            cout<<"Customer with ID "<<customerId<<" not found in the AVL Tree."<<endl;
            return;
        }
        if(root ->data->customerId == customerId){
            cout<< root -> data -> customerId<<","<<root -> data -> firstName<<","<<root -> data -> lastName<<","<<root -> data ->city<<","<<root -> data ->company<<","<<root -> data -> country<<","<<root -> data -> subscriptionDate<<endl;
            return;
        }
        if(customerId < root->data->customerId){
            SearchBalanceIndex(root->left, customerId);
        }else{
            SearchBalanceIndex(root->right, customerId);
        }
    }
};

struct MinHeap {
    Node* heaparray[1000];
    int size;
    MinHeap(){
        size = 0;
    }
      void AddSubscriptionrecord(Node* customer ){ //insertion
        if (size==1000){
            cout<<"Heap is full"<<endl;
            return;
        }
            heaparray[size]= customer ;
            size++;
            int i = size-1;
            promoteEarliestSubscriber(i);
      }
      void promoteEarliestSubscriber(int i){ // promote oldest subscriber on top
        while (i!=0 &&  heaparray[i]->subscriptionDate < heaparray[(i-1)/2]->subscriptionDate){
                swap(heaparray[i], heaparray [(i-1)/2]);
                i = (i-1)/2;
            }
      }
       void buildSubscriptionPriorityQueue(){
        Node* temp = head ;
        while (temp != NULL){
            AddSubscriptionrecord(temp);
            temp = temp -> next;
        }
      }
      Node* getOldestSubscriber(){ //extract longest waiting subscriber (oldest)
        if (size <= 0){
            cout<<"Heap is empty"<<endl;
            return NULL;
        }
        Node* minCustomer = heaparray[0];
        cout<< "Extracting root: "<< heaparray[0]->customerId<<","<<heaparray[0]->firstName<<","<<heaparray[0]->lastName<<","<<heaparray[0]->city<<","<<heaparray[0]->company<<","<<heaparray[0]->country<<","<<heaparray[0]->subscriptionDate<<endl;
        heaparray[0] = heaparray [size-1];
        size--;
        reorderAfterExtraction(0);  // to fix heap
        return minCustomer;
      }
      
      void reorderAfterExtraction(int i){
        while (true){
            int smallest = i;
            int leftchild  = 2*i+1;
            int rightchild =2*i+2;

            if ( leftchild < size && heaparray[leftchild]->subscriptionDate < heaparray[smallest]->subscriptionDate){
                smallest = leftchild;
            }
            if ( rightchild < size && heaparray[rightchild]->subscriptionDate < heaparray[smallest]->subscriptionDate){
                smallest = rightchild;
            }
            if (smallest == i){
                break;
            }
            swap(heaparray[i], heaparray[smallest]);
            i = smallest;
        }    
    }
    void displayPriorityqueue() {
        cout << "Subscription Priority Queue (Min-Heap):" << endl;
        for (int i = 0; i < size; i++) {
            cout << "  Customer ID   : " << heaparray[i]->customerId << endl;
    cout << "  Name          : " <<heaparray[i]->firstName << " " <<heaparray[i]->lastName << endl;
    cout << "  Company       : " << heaparray[i]->company << endl;
    cout << "  City          : " <<heaparray[i]->city << endl;
    cout << "  Country       : " << heaparray[i]->country << endl;
    cout << "  Subscribed On : " <<heaparray[i]->subscriptionDate << endl; 
        }
    }

};
struct HashNode {
    Node* data ;
    HashNode* next;
    HashNode(Node* customer){
        data = customer;
        next = NULL;
    }
};
struct HashTable {
    HashNode*  hashtable [1001];
    int size =1001;
    HashTable(){
    for (int i = 0; i < 1001; i++){
        hashtable[i] = NULL;
    }
    }
     int generateCustomerHash(string customerid ){ //converting customer id into index
      int hashvalue=0;
      for(char c: customerid ){
        hashvalue +=c;
      } 
      return hashvalue % 1001;
    }

    void  addToDirectory(Node* customer ){ //inserting customer in hashtable
        int index = generateCustomerHash(customer->customerId);
        if ( hashtable[index]==NULL){
            hashtable[index] = new HashNode(customer);
        }else{
            HashNode* newNode = new HashNode(customer);
            newNode->next = hashtable[index];
            hashtable[index] = newNode;
        }
    }
    void buildHashDirectory (){
        Node*  temp = head;
        while ( temp!=NULL){
            addToDirectory(temp);
            temp= temp->next ;
        }
    }
    void findCustomerInstantly(string customerID){ // search
        int index = generateCustomerHash(customerID);
        HashNode* temp = hashtable [index];
        while(temp != NULL){
            if(temp -> data -> customerId == customerID){
                cout << "CUSTOMER FOUND!\n"<<  endl;
                     cout << "  Customer ID   : " << temp->data->customerId << endl;
    cout << "  Name          : " <<temp-> data->firstName << " " <<temp-> data->lastName << endl;
    cout << "  Company       : " << temp->data->company << endl;
    cout << "  City          : " << temp->data->city << endl;
    cout << "  Country       : " << temp->data->country << endl;
    cout << "  Subscribed On : " <<temp->data-> subscriptionDate << endl;   
                return;
            }
            temp = temp -> next;
        }
        cout << "Customer Not Found" << endl;  
    }
    void removeFromDirectory(string customerID){  //delete
        int index = generateCustomerHash(customerID);
        HashNode* temp = hashtable [index];
        if (temp == NULL){
            cout<<"Customer with ID "<<customerID<<" not found in the directory."<<endl;
            return;
        }
        else if (temp->data->customerId == customerID) { //first node
            hashtable[index]= temp->next;
            delete temp ;
            cout<<"Customer with ID "<<customerID<<" removed from the directory."<<endl;
        }
        else { //mid or last Node
           HashNode* prev= NULL; 
             while ( temp != NULL && temp->data->customerId != customerID){
                prev = temp ; 
                temp = temp -> next;
            }
              if(temp == NULL){
                cout << "Customer with ID " << customerID << " not found in the directory." << endl;
                return;
            }
              prev -> next = temp -> next;
              delete temp ; 
              cout<<"Customer with ID "<<customerID<<" removed from the directory."<<endl;  

        }
    }
     void displayHashDirectory(){
        cout << "Customer Directory (Hash Table):" << endl;
        for (int i = 0; i < size; i++){
            HashNode* temp = hashtable[i];
            while (temp != NULL){
                    cout << "  Customer ID   : " << temp->data->customerId << endl;
    cout << "  Name          : " <<temp-> data->firstName << " " <<temp-> data->lastName << endl;
    cout << "  Company       : " << temp->data->company << endl;
    cout << "  City          : " << temp->data->city << endl;
    cout << "  Country       : " << temp->data->country << endl;
    cout << "  Subscribed On : " <<temp->data-> subscriptionDate << endl;    
               temp = temp -> next;
            }
        }
     }
};
void swapCustomerRecords(Node* a,Node* b){ //swap two nodes
    swap(a->customerId, b->customerId);
    swap(a->firstName, b->firstName);
    swap(a->lastName, b->lastName);
    swap(a->company, b->company);
    swap(a->city, b->city);
    swap(a->country,b->country);
    swap(a->subscriptionDate, b->subscriptionDate);
}
void bubbleSortByLastName() {
    if (head == NULL){
        cout<<"No Data Found"<<endl;
        return;
    }
    bool swapp = true;
    while (swapp) { 
        swapp = false;
        Node* temp = head;
        while (temp->next != NULL) {
            if (temp->lastName > temp->next->lastName) {
                swapCustomerRecords(temp,temp-> next);
                swapp = true;
            }
            temp = temp->next;
        }
    }
}
void buildArray(vector<Node*> &arr) {
    Node* temp = head;
    while (temp != NULL) {
        arr.push_back(temp);
        temp = temp->next;
    }
}
void fastLookUpByLastName(string key){ //binary search
    vector<Node*> arr;
    buildArray(arr);
    int start = 0;
    int end = arr.size() - 1;
    while(start <= end){
        int mid = (start + end) / 2;
        if(arr[mid] -> lastName == key){
            cout << "CUSTOMER FOUND!\n"<< endl;
                 cout << "  Customer ID   : " << arr[mid]->customerId << endl;
    cout << "  Name          : " <<arr[mid]->firstName << " " <<arr[mid]->lastName << endl;
    cout << "  Company       : " << arr[mid]->company << endl;
    cout << "  City          : " <<arr[mid]->city << endl;
    cout << "  Country       : " << arr[mid]->country << endl;
    cout << "  Subscribed On : " <<arr[mid]-> subscriptionDate << endl;   
            return;
        }
        else if(arr[mid] -> lastName < key){
            start = mid +1;
        }
        else{
            end = mid - 1;
        }
    }
     cout << "Customer Not Found" << endl;    
}
//  selection sort 
void sortBySubscription (){
     if ( head==NULL ){
        cout<<"No Data Found"<<endl;
        return;
     }
     Node* curr = head; 
     Node* temp = NULL ;
      Node* min_node = curr;
     while ( curr!= NULL){
        min_node = curr;
         temp= curr->next ; 
        while ( temp != NULL){
             if ( temp->subscriptionDate < min_node->subscriptionDate){
                min_node = temp ;

             }
              temp= temp->next;
        }
        if ( min_node!=curr){
            swapCustomerRecords(curr, min_node);
        }
         curr= curr->next;
     }
     
    } 

 // merge sort 
 
 Node*  find_middle (Node* head){
     Node* slow= head ; 
      Node* fast = head->next  ; 
       while (fast!=NULL && fast->next!=NULL){
        slow=slow->next;
        fast = fast->next->next;
       }
        return slow;

 }

void fixPrevPointers() {
    Node* temp = head;
    Node* prevNode = NULL;
    while (temp != NULL) {
        temp->prev = prevNode;
        prevNode = temp;
        temp = temp->next;
    }
    
    tail = prevNode;
}
 Node* merge (Node* left , Node* right ){
    if ( left==NULL){
        return right ;
    }
    if ( right ==NULL){
         return left  ;
    }
    Node* result =NULL;

     if  (left->country <right->country){
         result = left; 
         result->next =merge (left->next , right); 

     }else {
        result = right ; 
         result->next = merge ( left , right->next );
     }
     return result ; 
 }

 Node* sortbycountry (Node* head ){
     if ( head ==NULL || head->next == NULL){
        return head ;
     }
     Node* middle = find_middle(head );
     Node* second = middle->next ;
     middle->next = NULL;
     Node* left =sortbycountry(head);
     Node*  right = sortbycountry(second);
        return merge ( left , right );
    
 }
struct graphNode  {
 string country ; 
  int weight ; 
    graphNode* next;
    graphNode(string country, int weight){
        this->country = country;
        this->weight = weight;
        next = NULL;
    }
};
struct  st_for_dfs{
    int array[1001];
    int top ;
    st_for_dfs(){
        top = -1;
    }
    void  push ( int value ){
        if (top == 1000){
            cout<<"Stack is full"<<endl;
            return;
        }
        top++;
        array[top] = value;
    }
    void pop (){
        if (top == -1){
            cout<<"Stack is empty"<<endl;
            return;
        }
        top--;
    }
};
struct Edge {
    int u, v;
    int wt;
    Edge(int u, int v, int wt) {
        this->u = u;
        this->v = v;
        this->wt = wt;
    }
};
struct Graph {   // graph is implemented on country not customer(whole node)
    graphNode* adjancylist [1001];
    string countries[1001];
    int size = 1001;
    int countryCount =0;    // Number of vertices
    vector<Edge> edgeList;
    Graph (){
        for ( int i =0; i < size; i++){
            adjancylist[i] = NULL;
        }
    }
    bool check_country_in_array(string country){  // check whether that country already exists in array 
         for (int i =0; i < countryCount;i++){
            if(country ==  countries[i]){
                return true ;
            }
        } return false ; 
    }
    void extractCountry (){    //extracting unique countries 
        Node* temp = head; 
         while ( temp!=NULL){
            bool found =  check_country_in_array(temp->country);
             if ( found == false ){
                countries[countryCount] = temp->country;
                countryCount++;
             }
             temp = temp->next ; 
         }
    }
    int  customer_count(string country ){ // to calculate edge weight 
        Node* temp = head ; 
        int count =0;
         while ( temp !=  NULL ){
            if ( temp->country == country ){
                count++;
            }
            temp = temp->next;
         }
          return count ;
    }
     int weightcount ( string countryA , string countryb){   // calculating edge weight between 2 countries based on number of customers
          int custoemrA = customer_count(countryA);
          int custoemrB = customer_count(countryb); 
           int weight = abs (custoemrA - custoemrB);
           return weight ;
     } 
     // addedge 
      void  linemarket(){
        extractCountry ();
        for ( int i =0 ; i < countryCount ;i++){
            for ( int j =i+1; j < countryCount ;j++){
                if (i == j){
                    continue;
                }
                int weight = weightcount(countries[i], countries [j]);
                if(weight < 200){   
                    graphNode* newnode = new graphNode(countries[j], weight);
                        newnode->next = adjancylist[i];
                        adjancylist[i] = newnode;

                    graphNode* newnode2 = new graphNode(countries[i], weight);
                        newnode2->next = adjancylist[j];
                        adjancylist[j] = newnode2;
            
                }
            }
        }

    }
    // dfs 
     void exploremarketdepth (int countryindex ){
        if (countryindex < 0 || countryindex >= countryCount){
            return;
        }
         bool visited [1001]={false};

         st_for_dfs  st ;
         visited[countryindex] = true;
          st.push(countryindex);
          while (st.top>=0){
            int currentindex= st.array[st.top];
            st.pop();
            cout << countries[currentindex] << endl;
            graphNode* temp = adjancylist[currentindex];
            while ( temp!=NULL){
                int neighborindex = -1 ;
                for (int i = 0 ; i < countryCount ;i++){
                    if ( countries[i] == temp->country){
                        neighborindex = i ;
                        break;
                    }
                }
                if (neighborindex != -1 && visited[neighborindex] == false) {
                visited[neighborindex] = true;  
                st.push(neighborindex);
                }
                temp = temp->next;

            }
          }
     }
//  prims algorithm 
     void find_minimum_market_span_tree_prim(int startindex){
        bool visited[1001]={ false} ;
        int key[1001];
        int parent [1001];
        for ( int i =0; i < countryCount ;i++){
            key[i] = 99999;
            parent[i] = -1;
             visited[i]  =false;

        }
         
        key[startindex] = 0;
        for (int c =0 ; c< countryCount-1;c++ ){
            int min = 9999999;
            int u = -1;
            
            for ( int i =0;i< countryCount ;i++){
                if ( visited[i]==false && key[i]<min  ){
                    min = key[i];
                    u=i;
                }


        }if(u == -1) return;
         visited[u]    =true;
        graphNode* temp = adjancylist[u];
        while (temp!=NULL){
            
            // index find of that neightbor 
            int index_of_country=-1;
             for ( int i =0; i < countryCount ;i++){
                if ( countries[i] == temp->country){
                    index_of_country = i;
                    break;
                }

             }

        
        if ( index_of_country !=-1 && visited[index_of_country]==false &&  temp->weight<key[index_of_country]){
            parent[index_of_country] = u ;
            key[index_of_country] = temp->weight;
        }
        temp=temp->next;
    }
        }
        int total_weight =0;
         cout << "Minimum Market Spanning Tree (Prim's Algorithm):" << endl;
        for (int i = 0; i < countryCount; i++) {
            if (parent[i] != -1) {
                cout << countries[parent[i]] << " -- " << countries[i] << " (Weight: " << key[i] << ")" << endl;
            total_weight += key[i];
            }


     } cout << "Total Weight of the Minimum Market Spanning Tree: " << total_weight << endl;
    

    }
   // BFS
void FindNearstMarkets(int startindex){
    if(startindex < 0 || startindex >= countryCount){
        return;
    }
    bool visited[1001] = {false};
    queue<int> q;
    visited[startindex] = true;
    q.push(startindex);
    while(!q.empty()){
        int current = q.front();
        q.pop();
        cout << countries[current] << endl;
        graphNode* temp = adjancylist[current];
        while(temp != NULL){
            int neighborindex = -1;
            for(int i = 0; i < countryCount; i++){
                if(countries[i] == temp->country){
                    neighborindex = i;
                    break;
                }
            }
            if(neighborindex != -1 && visited[neighborindex] == false){
                visited[neighborindex] = true;
                q.push(neighborindex);
            }

            temp = temp->next;
        }
    }
}
//Buid edges
void connectCustomerMarkets() {
    edgeList.clear();

    for (int i = 0; i < countryCount; i++) {
        graphNode* temp = adjancylist[i];

        while (temp != NULL) {
            int vIndex = -1;
            for (int j = 0; j < countryCount; j++) {
                if (countries[j] == temp->country) {
                    vIndex = j;
                    break;
                }
            }
            if (vIndex != -1 && i < vIndex) {
                edgeList.push_back(Edge(i, vIndex, temp->weight));
            }

            temp = temp->next;
        }
    }
}
    int findParent(int v, vector<int>& parent) {
    if (parent[v] == v) {
        return v;
    }
    return parent[v] = findParent(parent[v], parent);
  }

  //unionSet
void mergeMarketRegions(int a, int b, vector<int>& parent) {
    a = findParent(a, parent);
    b = findParent(b, parent);
    if (a != b) {
        parent[a] = b;
    }
}
// kruskalMST
void buildCostEfficient_kruskal() {
    connectCustomerMarkets();
    // sort edges
    for (int i = 0; i < edgeList.size() - 1; i++) {
        for (int j = 0; j < edgeList.size() - i - 1; j++) {
            if (edgeList[j].wt > edgeList[j + 1].wt) {
                swap(edgeList[j], edgeList[j + 1]);
            }
        }
    }

    vector<int> parent(countryCount);
    for (int i = 0; i < countryCount; i++) {
        parent[i] = i;
    }

    cout << "\nKruskal MST:\n";

    for (Edge e : edgeList) {
        int pu = findParent(e.u, parent);
        int pv = findParent(e.v, parent);

        if (pu != pv) {
            cout << countries[e.u] << " -- " 
                 << countries[e.v] << " ("
                 << e.wt << ")\n";

            mergeMarketRegions(pu, pv, parent);
        }
    }
}
//dijkstra
void findingOptimalExpansionRoute(int src) {
    vector<int> dist(countryCount, INT_MAX);
    vector<bool> visited(countryCount, false);

    dist[src] = 0;

    for (int i = 0; i < countryCount; i++) {

        int u = -1;
        int minDist = INT_MAX;

        for (int j = 0; j < countryCount; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1){
             return;
        }

        visited[u] = true;

        graphNode* temp = adjancylist[u];

        while (temp != NULL) {

            int vIndex = -1;
            for (int j = 0; j < countryCount; j++) {
                if (countries[j] == temp->country) {
                    vIndex = j;
                    break;
                }
            }

            if (vIndex != -1) {
                if (dist[u] + temp->weight < dist[vIndex]) {
                    dist[vIndex] = dist[u] + temp->weight;
                }
            }

            temp = temp->next;
        }
    }

    cout << "\nDijkstra Shortest Paths from " << countries[src] << ":\n";
    for (int i = 0; i < countryCount; i++) {
        cout << countries[i] << " = " << dist[i] << "\n";
    }
}
};
    void loadFromFile(){
    ifstream fin;
    fin.open("customers-1000.csv");
    if (!fin.is_open()) {
        cout << "Error: Could not open customers-1000.csv\n";
        return;
    }
    string line, word;
    vector<string> lineData;
    int lines = 0;

    while (!fin.eof()) {
        getline(fin, line);
        if (line.empty()) continue;
        stringstream s(line);
        bool inQuotes = false;
        string field = "";
        for (int i = 0; i < (int)line.size(); i++) {
            char c = line[i];
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                lineData.push_back(field);
                field = "";
            } else {
                field += c;
            }
        }
        lineData.push_back(field);
        if (lines != 0 && lineData.size() >= 11) {
            addNode(lineData[1],lineData[2],lineData[3],lineData[4],lineData[5],lineData[6],lineData[10]);
        }
        lineData.clear();
        lines++;
    }
    fin.close();
    cout << (lines - 1) << " customers loaded from file.\n";
    };
int main() {
    loadFromFile();

    bst b;
    TreeNode* bstRoot = NULL;
    b.buildbst(bstRoot);

    AVLTree avl;
    TreeNode* avlRoot = NULL;
    avl.buildBalanceIndex(avlRoot);

    MinHeap heap;
    heap.buildSubscriptionPriorityQueue();

    HashTable ht;
    ht.buildHashDirectory();

    Graph g;
    g.linemarket();

    Queue q;

    int choice;
    do {
        cout << "\n";
        cout << "========================================================\n";
        cout << "       CUSTOMER RELATIONSHIP MANAGEMENT SYSTEM          \n";
        cout << "          Powered by Advanced DSA Engine                \n";
        cout << "========================================================\n";
        cout << "  CUSTOMER REGISTRY (Linked List)\n";
        cout << "  1.  View All Customers\n";
        cout << "  2.  View Customers (Newest First)\n";
        cout << "  3.  Search Customer by Name\n";
        cout << "  4.  Count Customers by Country\n";
        cout << "  5.  Remove All Customers from a Country\n";
        cout << "--------------------------------------------------------\n";
        cout << "  UNDO SYSTEM (Stack)\n";
        cout << "  6.  Undo Last Deletion\n";
        cout << "  7.  View Undo Log\n";
        cout << "  8.  Check Undo Log Size\n";
        cout << "--------------------------------------------------------\n";
        cout << "  SUBSCRIPTION QUEUE (Queue)\n";
        cout << "  9.  Load All Customers into Processing Queue\n";
        cout << "  10. Process Next Customer in Queue\n";
        cout << "  11. View Processing Queue\n";
        cout << "--------------------------------------------------------\n";
        cout << "  FAST SEARCH (BST)\n";
        cout << "  12. Search Customer by ID (BST)\n";
        cout << "  13. View All Customers Sorted by ID (BST Inorder)\n";
        cout << "  14. Delete Customer from BST by ID\n";
        cout << "--------------------------------------------------------\n";
        cout << "  BALANCED SEARCH (AVL Tree)\n";
        cout << "  15. Search Customer by ID (AVL Tree)\n";
        cout << "  16. View All Customers Sorted by ID (AVL Inorder)\n";
        cout << "--------------------------------------------------------\n";
        cout << "  PRIORITY SYSTEM (Min Heap)\n";
        cout << "  17. Get Oldest Subscriber (Loyalty Priority)\n";
        cout << "  18. Display Full Subscription Priority Queue\n";
        cout << "--------------------------------------------------------\n";
        cout << "  INSTANT LOOKUP (Hash Table)\n";
        cout << "  19. Find Customer Instantly by ID\n";
        cout << "  20. Remove Customer from Directory\n";
        cout << "  21. Display Hash Directory\n";
        cout << "--------------------------------------------------------\n";
        cout << "  SORTING\n";
        cout << "  22. Sort Customers Alphabetically by Last Name (Bubble)\n";
        cout << "  23. Sort Customers by Subscription Date (Selection)\n";
        cout << "  24. Sort Customers by Country (Merge Sort)\n";
        cout << "  25. Fast Lookup by Last Name (Binary Search)\n";
        cout << "--------------------------------------------------------\n";
        cout << "  MARKET INTELLIGENCE (Graph)\n";
        cout << "  26. Find Nearest Markets - BFS\n";
        cout << "  27. Explore Market Depth - DFS\n";
        cout << "  28. Find Optimal Expansion Route - Dijkstra\n";
        cout << "  29. Minimum Market Spanning Tree - Prim's\n";
        cout << "  30. Cost Efficient Market Network - Kruskal's\n";
        cout << "========================================================\n";
        cout << "  0.  Exit System\n";
        cout << "========================================================\n";
        cout << "  Enter your choice: ";
        cin >> choice;
        cin.ignore();

        cout << "\n";

        if (choice == 1) {
            cout << "--- COMPLETE CUSTOMER REGISTRY ---\n";
            printAll();

        } else if (choice == 2) {
            cout << "--- CUSTOMER REGISTRY (NEWEST FIRST) ---\n";
            reversePrint();

        } else if (choice == 3) {
            string name;
            cout << "Enter customer first or last name: ";
            getline(cin, name);
            Node* result = search_by_name(name);
            if (result)
                cout << "FOUND: " << result->customerId << " | "
                     << result->firstName << " " << result->lastName
                     << " | " << result->country
                     << " | Subscribed: " << result->subscriptionDate << endl;
            else
                cout << "No customer found with name: " << name << endl;

        } else if (choice == 4) {
            string country;
            cout << "Enter country name: ";
            getline(cin, country);
            int count = countbyCountry(country);
            cout << "Total customers from " << country << ": " << count << endl;

        } else if (choice == 5) {
            string country;
            cout << "Enter country to remove customers from: ";
            getline(cin, country);
            int before = countbyCountry(country);
            deleteByCountry(country);
            cout << before << " customers from " << country << " removed and saved to undo log.\n";

        } else if (choice == 6) {
            s1.undoLastDeletion();

        } else if (choice == 7) {
            cout << "--- UNDO LOG (Deleted Customers) ---\n";
            s1.displayUndoLog();

        } else if (choice == 8) {
            cout << "Undo log currently holds "
                 << s1.getUndoLogSize() << " deleted record(s).\n";

        } else if (choice == 9) {
            Node* temp = head;
            int count = 0;
            while (temp != NULL) {
                q.enqueue(temp);
                temp = temp->next;
                count++;
            }
            cout << count << " customers loaded into processing queue.\n";

        } else if (choice == 10) {
            cout << "Processing next customer in subscription queue:\n";
            q.dequeue();

        } else if (choice == 11) {
            cout << "--- SUBSCRIPTION PROCESSING QUEUE ---\n";
            q.displayByQueue();

        } else if (choice == 12) {
            string id;
            cout << "Enter Customer ID to search: ";
            getline(cin, id);
            cout << "BST Search Result:\n";
            b.search(bstRoot, id);

        } else if (choice == 13) {
            cout << "--- ALL CUSTOMERS SORTED BY ID (BST) ---\n";
            b.inorder(bstRoot);

        } else if (choice == 14) {
            string id;
            cout << "Enter Customer ID to delete from BST: ";
            getline(cin, id);
            b.deleteBST(bstRoot, id);

        } else if (choice == 15) {
            string id;
            cout << "Enter Customer ID to search (AVL): ";
            getline(cin, id);
            cout << "AVL Search Result:\n";
            avl.SearchBalanceIndex(avlRoot, id);

        } else if (choice == 16) {
            cout << "--- ALL CUSTOMERS SORTED BY ID (AVL) ---\n";
            avl.inorder(avlRoot);

        } else if (choice == 17) {
            cout << "--- HIGHEST PRIORITY CUSTOMER (Earliest Subscriber) ---\n";
            heap.getOldestSubscriber();

        } else if (choice == 18) {
            cout << "--- FULL SUBSCRIPTION PRIORITY QUEUE ---\n";
            heap.displayPriorityqueue();

        } else if (choice == 19) {
            string id;
            cout << "Enter Customer ID for instant lookup: ";
            getline(cin, id);
            ht.findCustomerInstantly(id);

        } else if (choice == 20) {
            string id;
            cout << "Enter Customer ID to remove from directory: ";
            getline(cin, id);
            ht.removeFromDirectory(id);

        } else if (choice == 21) {
            cout << "--- CUSTOMER HASH DIRECTORY ---\n";
            ht.displayHashDirectory();

        } else if (choice == 22) {
            bubbleSortByLastName();
            cout << "Customers sorted alphabetically by last name.\n";
            cout << "Use option 1 to view sorted list.\n";

        } else if (choice == 23) {
            sortBySubscription();
            cout << "Customers sorted by subscription date (oldest first).\n";
            cout << "Use option 1 to view sorted list.\n";

        } else if (choice == 24) {
            head = sortbycountry(head);
            fixPrevPointers();
            cout << "Customers sorted by country.\n";
            cout << "Use option 1 to view sorted list.\n";

        } else if (choice == 25) {
            string name;
            cout << "NOTE: Make sure list is sorted by last name first (option 22).\n";
            cout << "Enter last name to search: ";
            getline(cin, name);
            fastLookUpByLastName(name);

        } else if (choice == 26) {
            string country;
            cout << "Enter starting country for BFS market scan: ";
            getline(cin, country);
            int idx = -1;
            for (int i = 0; i < g.countryCount; i++) {
                if (g.countries[i] == country) { idx = i; break; }
            }
            if (idx == -1) cout << "Country not found in market network.\n";
            else g.FindNearstMarkets(idx);

        } else if (choice == 27) {
            string country;
            cout << "Enter starting country for DFS market exploration: ";
            getline(cin, country);
            int idx = -1;
            for (int i = 0; i < g.countryCount; i++) {
                if (g.countries[i] == country) { idx = i; break; }
            }
            if (idx == -1) cout << "Country not found in market network.\n";
            else g.exploremarketdepth(idx);

        } else if (choice == 28) {
            string country;
            cout << "Enter source country for optimal expansion route: ";
            getline(cin, country);
            int idx = -1;
            for (int i = 0; i < g.countryCount; i++) {
                if (g.countries[i] == country) { idx = i; break; }
            }
            if (idx == -1) cout << "Country not found in market network.\n";
            else g.findingOptimalExpansionRoute(idx);

        } else if (choice == 29) {
            cout << "--- MINIMUM MARKET SPANNING TREE (Prim's) ---\n";
            g.find_minimum_market_span_tree_prim(0);

        } else if (choice == 30) {
            cout << "--- COST EFFICIENT MARKET NETWORK (Kruskal's) ---\n";
            g.buildCostEfficient_kruskal();

        } else if (choice != 0) {
            cout << "Invalid choice. Please enter a number from the menu.\n";
        }

    } while (choice != 0);

    cout << "\n========================================================\n";
    cout << "   Thank you for using the CRM System. Goodbye!\n";
    cout << "========================================================\n";
    return 0;
}