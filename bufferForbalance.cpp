//new version
bool RBTree::remove(int key){
    Node* node = fetch(key);

    if(node == null){
        cout << "Error: key " << key << " does not exits!" << endl;
        return false;
    }

    if(node->pos == -1){
        cout << "Error: key " << ket << "does not exits!" << endl;
        return false;
    }

    Node* rightNode = node->right;
    Node* leftNode = node->left;




    //update cache
    //----notice that node's old pos is reusable
    //----put it in somewhere
    //----sp that it can be considered first when add a new node
    //check if delete nodes can is full
    //----if full, open data file and update data file
    //----clear delete nodes can






    //if node has right subtree
    if( (rightNode != NULL) && (rightNode->pos != -1) ){

        //update node pos with the smallest node in right subtree
        // then delete the smallest node
        Node* minNode = minNodeOf(rightNode);

        node->pos = minNode->pos;

        // if minNode is red, simply delete it
        if(minNode->color == RED){
            if(minNode == minNode->father->right){
                minNode->father->right = new Node;
            }else{
                minNode->father->left = new Node;
            }
            delete minNode;

            return true;
        }

        //if minNode is BLACK
        // see if minNode has right child
        // if it has right chlid, replace it with it's child(color it BALCK)
        Node* rightOfMin = minNode->right;

        if( (rightOfMin != NULL) && (rightOfMin->pos != -1)){
            //if right chlid exits, it must be RED
            rightOfMin->color = BLACK;

            if(minNode == minNode->father->left){
                minNode->father->left = rightOfMin;
            }else{
                //if the minNode is rightNode itself, it will be right child
                minNode->father->right = rightOfMin;
            }

            delete minNode;

            return true;

        }else{
            //minNode has no child
            // we get a double black node
            delete minNode;
            minNode = new Node;
            minNode->color = BLACK_BLACK;
            doubleBlack(minNode);

            return true;
        }
    
    //if node has left subtree
    }else if( (leftNode != NULL) && (leftNode->pos != -1) ){
        Node* maxNode = maxNodeOf( leftNode );

        node->pos = maxNode->pos;

        //if maxNode is RED, simply delete it
        if(maxNode->color == RED){
            if(maxNode == maxNode->father->right){
                maxNode->father->right = new Node;
            }else{
                maxNode->father->left = new Node;
            }
            delete maxNode;

            return true;            
        }

        Node* leftOfMax = maxNode->left;

        if( leftOfMax != NULL && leftOfMax->pos != -1 ){
            //leftOfMax must be RED
            leftOfMax->color = BLACK;

            if(maxNode == maxNode->father->left){
                maxNode->father->left = leftOfMax;
            }else{
                //if the maxNode is leftNode itself, it will be left child
                maxNode->father->right = leftOfMax;
            }

            delete maxNode;

            return true;            
        }else{
            //maxNode has no child
            // we will get a double black node

            delete maxNode;
            maxNode = new Node;
            maxNode->color = BLACK_BLACK;
            doubleBlack(maxNode);

            return true;
        }

    }else{
        //node is a leaf, has no child

        // if node is root
        if(node == root){
            delete root;
            root = new Node;
            return true;
        }

        Node* newNode = newNode;
        if(node->father->right == node){
            node->father->right = newNode;
        }else{
            node->father->left = newNode;
        }

        delete newNode;
        return true;

    }
}


void RBTree::doubleRed(Node* & node){
    if(node == root){
        node->color = BLACK;
        return;
    }

    Node* grandpa = node->father;
    if(node == grandpa->right){
        Node* uncle = grandpa->left;
    }else{
        Node* uncle = grandpa->right;
    }

    if(uncle->color == RED){
        grandpa->color = RED;
        uncle->color = node->color = BLACK;
    }else{
        grandpa->color = RED;
        uncle->color = BLACK_BLACK;
        node->color = BLACK;

        doubleBlack(uncle);
    }

    if(root->color == RED){
        root->color = BLACK;
    }
}