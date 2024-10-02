#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Logica y codigo basado en https://www.geeksforgeeks.org/insertion-in-an-avl-tree/ y 
// https://www.enjoyalgorithms.com/blog/avl-tree-data-structure y ayuda de ChatGPT para arreglar problemas

template <typename T>
struct NodeBT {
    T data;
    NodeBT* left;
    NodeBT* right;
    int height;
};


template <typename T>
class AVLTree {

    NodeBT<T>* root;

public:

    AVLTree() : root(NULL) {} // Inicializo el root como null 

    // Aqui saco el root
    NodeBT<T>* getroot(){
        return root;
    }

    NodeBT<T>* insert(NodeBT<T>* node, T value){
        if(node==NULL){
            // Si es el caso del HEAD es NULL, entra aqui
            NodeBT<T>* nuevo= new NodeBT<T>;
            nuevo->data=value;
            nuevo->left=NULL;
            nuevo->right=NULL;
            nuevo->height=1;
            node=nuevo;
            //cout<<"Inserte el primer valor"<<endl;
            return node;
        }
        else if(value < node->data){
            if(node->left==NULL){
                //cout<<"Inserte el valor al lado izquierdo"<<endl;
                NodeBT<T>* nuevo = new NodeBT<T>;
                nuevo->data=value;
                nuevo->left=NULL;
                nuevo->right=NULL;
                nuevo->height=1;
                node->left=nuevo;
            }else{
                node->left=insert(node->left, value);
            }

        }else if(value > node->data){
            if(node->right==NULL){
                //cout<<"Inserte el valor al lado derecho"<<endl;
                NodeBT<T>* nuevo = new NodeBT<T>;
                nuevo->data=value;
                nuevo->left=NULL;
                nuevo->right=NULL;
                nuevo->height=1;
                node->right=nuevo;
            }else{
                node->right=insert(node->right, value);
            }
        }



        // Se hace el update del height
        updateHeight(node);

        //Obtengo el factor de balance y verifico donde esta el desbalance
        int fbal=fb(node);
        if(fbal>1){
            //cout<<"Voy a rotar porque esta mas alto a la izquierda"<<endl;
            if(fb(node->left)>=0){ // el mismo signo
                return rotateRight(node);
            }else{
                return rotateLeftRight(node);
            }
        } else if(fbal<-1){
            //cout<<"Voy a rotar porque esta mas alto a la derecha"<<endl;
            if(fb(node->right)<=0){ // el mismo signo
                return rotateLeft(node);
            }else{
                return rotateRightLeft(node);
            }
        }
        // Retornar el nodo
        return node;

    }

    // Esta funcion se realiza para poder manejar los casos en los que el hijo sea NULL (hojas) y poder obtener instantaneamente el 0 en height de los hijos vacios
    // https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
    int getHeight(NodeBT<T>* node){
        if(node!=NULL){
            return node->height;
        }else{
            return 0;
        }

    }

    void updateHeight(NodeBT<T>* node){
        if(node!=NULL){
            node->height=1+max(getHeight(node->left),getHeight(node->right));
        }else{
            return;
        }
    }

    // Devuelvo el puntero hacia donde esta
    NodeBT<T>* rotateLeft(NodeBT<T>* node){

        // Defino los punteros hacia la estructura, solo cambio los que cambian
        NodeBT<T>* newRoot = node->right;
        NodeBT<T>* newRootLeft = node;
        NodeBT<T>* newRootLeftRight = node->right->left;

        // Conecto la nueva estructura con los punteros que cambian
        newRoot->left=newRootLeft;
        newRootLeft->right=newRootLeftRight;

        // Actualizo las alturas
        updateHeight(newRootLeft);
        updateHeight(newRoot);

        // Retorno el nuevo root del arbol o subarbol
        return newRoot;

    }

    NodeBT<T>* rotateRight(NodeBT<T>* node){

        // Defino los punteros hacia la estructura, solo cambio los que cambian

        NodeBT<T>* newRoot = node->left;
        NodeBT<T>* newRootRight = node;
        NodeBT<T>* newRootRightLeft = node->left->right;

        // Conecto la nueva estructura con los punteros que cambian
        newRoot->right=newRootRight;
        newRootRight->left=newRootRightLeft;

        // Actualizo las alturas
        updateHeight(newRootRight);
        updateHeight(newRoot);

        // Retorno el nuevo root del arbol o subarbol
        return newRoot;

    }

    NodeBT<T>* rotateLeftRight(NodeBT<T>* node){
        // Primero roto hacia la izquierda el arbol del hijo izquierdo del root
        node->left=rotateLeft(node->left);
        // Luego roto hacia la derecha el arbol del root
        NodeBT<T>* newRoot = rotateRight(node); // Ya estan haciendo el update de los h internamente
        return newRoot;
    }

    NodeBT<T>* rotateRightLeft(NodeBT<T>* node){
        // Primero roto hacia la derecha el arbol del hijo derecho del root
        node->right=rotateRight(node->right);
        // Luego roto hacia la izquierda el arbol del root
        NodeBT<T>* newRoot = rotateLeft(node); // Ya estan haciendo el update de los h internamente
        return newRoot;
    }



    // https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
    int fb(NodeBT<T>* node){
        return getHeight(node->left)-getHeight(node->right);
    }


    void insertNode(T value){
        root=insert(root,value);
    }


    // Realizo la busqueda de manera recursiva, pero necesito de entrada el root
    bool find(NodeBT<T>* node, T value){
        if(node == nullptr)
            return false;
        else if(value < node->data)
            return find(node->left, value);
        else if(value > node->data)
            return find(node->right, value);
        else
            return true;
    }

    bool search(T value){
        return find(root, value);
    }

    NodeBT<T>* findNode(NodeBT<T>* node,T value){
        if(node == nullptr)
            return NULL;
        else if(value < node->data)
            return findNode(node->left, value);
        else if(value > node->data)
            return findNode(node->right, value);
        else
            return node;
    }

    //Logica Basada en EnoyAlgorithms
    //https://www.enjoyalgorithms.com/blog/inorder-predecessor-binary-search-tree
    NodeBT<T>* findPredecesor(T value){

        if(root==NULL){
            // Si tu arbol esta vacio se entrega
            return NULL;
        }

        NodeBT<T>* temp = root;
        NodeBT<T>* predecesor = NULL;
        bool flag=false;

        while(temp!=NULL && flag!=true){
            // Voy a buscar el nodo que tiene el valor
            if(value<temp->data){ // Si el valor es menor que el valor del nodo, voy a la izquierda
                temp=temp->left;
            }
            else if(value>temp->data){ //Si el valor es mayor que el valor del nodo, voy a la guardo que el predecesor puede ser ese y voy a la derecha
                predecesor = temp;
                temp=temp->right;
            }else{
                //Si llega al valor pero si tiene un nodo izquierdo, en ese lado si o si esta su predecesor
                // Aqui se hace lo de clase
                if(temp->left!=NULL){
                    temp=temp->left;
                    while(temp->right!=NULL){
                        temp=temp->right;
                    }
                    predecesor=temp;
                }
                // Si no tiene algo a la izquierda en anterior predecesor queda como el predecesor
                //Rompemos el while
                flag=true;
            }
        }

        return predecesor;

    }

    //Logica Basada en EnoyAlgorithms
    //https://www.enjoyalgorithms.com/blog/inorder-successor-in-binary-search-tree
    NodeBT<T>* findSuccessor(T value){

        NodeBT<T>* temp = findNode(root,value);
        NodeBT<T>* successor = NULL;
        bool flag=false;

        if(root==NULL){
            // Si tu arbol esta vacio se entrega
            cout<<"Root vacio"<<endl;
            return NULL;
        }

        //Si llega al valor pero si tiene un nodo izquierdo, en ese lado si o si esta su predecesor
        // Aqui se hace lo de clase
        if(temp->right!=NULL){
            temp=temp->right;
            while(temp->left!=NULL){
                temp=temp->left;
            }
            successor=temp;
            flag=true;
        }

        temp=root;
        while(temp!=NULL && flag!=true){
            // Voy a buscar el nodo que tiene el valor
            if(value<temp->data){ // Si el valor es menor que el valor del nodo, voy a la guardo que el predecesor puede ser ese y voy a la izquierda
                successor = temp;
                temp=temp->left;
            }
            else if(value>temp->data){ //Si el valor es mayor que el valor del nodo, voy a la derecha
                temp=temp->right;
            }else{
                // Si no tiene algo a la izquierda en anterior predecesor queda como el predecesor
                //Rompemos el while
                flag=true;
            }
        }

        return successor;

    }

    // Funcion para visualizar mi arbol binario
    // Funcion generada por chatgpt solo para visualizacion
    void imprimirarbol(NodeBT<T>* node, int space) const {
        if (node == nullptr) {
            return;
        }

        space += 6;

        imprimirarbol(node->right, space);

        cout << endl;
        for (int i = 6; i < space; i++) {
            cout << " ";
        }
        cout << node->data << "\n";
        imprimirarbol(node->left, space);
    }

    void visualizararbol() const {
        imprimirarbol(root, 0);
    }

    void inorder(NodeBT<T>* node, vector<T>& vector){
        if (node == NULL) {
            return;
        }
        inorder(node->left,vector);
        vector.push_back(node->data);
        inorder(node->right,vector);
    }

    vector<T> inordertree(){
        vector<T> vector;
        inorder(root,vector);
        return vector;
    }

    void preorder(NodeBT<T>* node, vector<T>& vector){
        if (node == NULL) {
            return;
        }
        vector.push_back(node->data);
        preorder(node->left,vector);
        preorder(node->right,vector);
    }

    vector<T> preordertree(){
        vector<T> vector;
        preorder(root,vector);
        return vector;
    }

    void posorder(NodeBT<T>* node, vector<T>& vector){
        if (node != NULL) {
            posorder(node->left,vector);
            posorder(node->right,vector);
            vector.push_back(node->data);
        }


    }

    vector<T> posordertree(){
        vector<T> vector;
        posorder(root,vector);
        return vector;
    }

    NodeBT<T>* deleteinTree(NodeBT<T>* node, T value) //nuevo
    {
        // Caso base
        if (node == NULL){
            return node;
        }

        if (node->data > value){
            node->left = deleteinTree(node->left, value);
        }
        else if (node->data < value){
            node->right = deleteinTree(node->right, value);
        } else { //Si lo encuentra

            if (node->left == NULL) {
                NodeBT<T>* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == NULL) {
                NodeBT<T>* temp = node->left;
                delete node;
                return temp;
            }

            // Cuando ambos hijos estan pasa esto
            NodeBT<T>* successor = findPredecesor(node->data);
            node->data = successor->data;
            node->left = deleteinTree(node->left, successor->data);
            cout<<"Hallo predecesor"<<endl;

        }

        // Se hace el update del height
        updateHeight(node);

        //Obtengo el factor de balance y verifico donde esta el desbalance
        int fbal=fb(node);
        cout<<"Node data: "<<node->data<<" fb: "<<fbal<<endl;
        if(fbal>1){
            if(fb(node->left)>=0){ // el mismo signo
                cout<<"Roto a la derecha"<<endl;
                return rotateRight(node);
            }else{
                cout<<"Roto a la izquierda y luego derecha"<<endl;
                return rotateLeftRight(node);
            }
        } else if(fbal<-1){

            if(fb(node->right)<=0){ // el mismo signo
                cout<<"Roto a izquierda"<<endl;
                return rotateLeft(node);
            }else{
                cout<<"Roto a la izquierda y derecha"<<endl;
                return rotateRightLeft(node);
            }
        }
        // Retornar el nodo
        return node;
    }

    void deleteNode(T value){
        root=deleteinTree(root,value);
    }

    ///

    void buildBalancedArray(vector<int>& sortedArray, int start, int end, vector<int>& result) {
        if (start > end) {
            return;
        }

        int mid = (start + end) / 2;

        result.push_back(sortedArray[mid]);

        buildBalancedArray(sortedArray, start, mid - 1, result);

        buildBalancedArray(sortedArray, mid + 1, end, result);
    }

    vector<int> generateBalancedArray(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        vector<int> result;

        buildBalancedArray(arr, 0, arr.size() - 1, result);

        return result;
    }

    ///

    vector<int> getAllElements(NodeBT<int>* root1, NodeBT<int>* root2) {
        vector<int> result1;
        vector<int> result2;

        inorder(root1, result1);
        inorder(root2, result2);

        vector<int> merged = result1;
        merged.insert(merged.end(), result2.begin(), result2.end());

        sort(merged.begin(), merged.end());

        return merged;
    }



};

int main(){
    AVLTree<string> AVL;
    AVL.insertNode("Maio");
    AVL.insertNode("Marco");
    AVL.insertNode("Novembro");
    AVL.insertNode("Agosto");
    AVL.insertNode("Abril");
    AVL.insertNode("Janeiro");
    AVL.insertNode("Dezembro");
    AVL.insertNode("Julho");
    AVL.insertNode("Fevereiro");
    AVL.insertNode("Junho");
    AVL.insertNode("Outubro");
    AVL.insertNode("Setembro");

    // Visualizar arbol
    cout<<"Arbol anterior: "<<endl;
    AVL.visualizararbol();

    cout<<"------- Fin de primera prueba----------"<<endl;

    AVLTree<int> AVL1;
    AVL1.insertNode(4);
    AVL1.insertNode(5);
    AVL1.insertNode(7);
    AVL1.insertNode(2);
    AVL1.insertNode(1);
    AVL1.insertNode(3);
    AVL1.insertNode(6);
    // Visualizar arbol
    cout<<"Arbol anterior: "<<endl;
    AVL1.visualizararbol();

    // Inorder
    vector<string> inorder=AVL.inordertree();

    for(string nodo:inorder){
        cout<<nodo<<" , ";
    }
    cout<<endl;

    // Preorder
    vector<string> preorder=AVL.preordertree();

    for(string nodo:preorder){
        cout<<nodo<<" , ";
    }
    cout<<endl;

    // Posorder
    vector<string> posorder=AVL.posordertree();

    for(string nodo:posorder){
        cout<<nodo<<" , ";
    }
    cout<<endl;

    // Encontrar algo detallado de un arbol
    //cout<<AVL.findNode(AVL.getroot(),8)->left->data<<endl;

    AVLTree<int> AVL2;
    AVL2.insertNode(5);
    AVL2.insertNode(3);
    AVL2.insertNode(8);
    AVL2.insertNode(2);
    AVL2.insertNode(4);
    AVL2.insertNode(7);
    AVL2.insertNode(10);
    AVL2.insertNode(1);
    AVL2.insertNode(6);
    AVL2.insertNode(9);
    AVL2.insertNode(11);
    AVL2.visualizararbol();
    cout<<"-------Remuevo 4----------"<<endl;
    AVL2.deleteNode(4);
    AVL2.visualizararbol();
    cout<<"-------Remuevo 8----------"<<endl;
    AVL2.deleteNode(8);
    AVL2.visualizararbol();
    cout<<"-------Remuevo 6----------"<<endl;
    AVL2.deleteNode(6);
    AVL2.visualizararbol();
    cout<<"-------Remuevo 5----------"<<endl;
    AVL2.deleteNode(5);
    AVL2.visualizararbol();
    cout<<"-------Remuevo 2----------"<<endl;
    AVL2.deleteNode(2);
    AVL2.visualizararbol();
    cout<<"-------Remuevo 1----------"<<endl;
    AVL2.deleteNode(1);
    AVL2.visualizararbol();
    cout<<"-------Remuevo 7----------"<<endl;
    AVL2.deleteNode(7);
    AVL2.visualizararbol();
    cout<<"-------Remuevo 11----------"<<endl;
    AVL2.deleteNode(11);
    AVL2.visualizararbol();

}