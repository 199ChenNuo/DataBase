//new version:
bool RBTree::remove(int key){
    Node* node = fetch(key);

    if(node == NULL){
        cout << "Error: key " << key << " does not exits!" << endl;
        return;
    }

    if(node->pos == -1){
        cout << "Error: key " << key << " does not exits!" << endl;
        return;
    }

    //put node->pos into reusable poses 

    Node* rightNode = node->right;
    Node* leftNode  = node->left;


    if( (rightNode != NULL) && (rightNode->pos != -1) ){
        Node* minNode = minNodeOf( rightNode );

        //update node->pos
        node->pos = minNode->pos;

        //update father and child relationship
        Node* newNode = new Node;
        newNode->father = minNode->father;
        if(minNode == minNode->father->right){
            minNode->father->right = newNode;
        }else{
            minNode->father->left = newNode;
        }
        
        //make the tree balance again
        if(minNode->color == BLACK){
            newNode->color = BLACK_BLACK;
            balance(newNode->father);
        }

        //release space
        delete minNode;
        return true;

    }

    else if( (leftNode != NULL) && (leftNode->pos != -1) ){
        Node* maxNode = maxNodeOf( leftNode );

        //update node->pos
        node->pos = maxNode->pos;

        //update father and child relationship
        Node* newNode = new Node;
        newNode->father = maxNode->father;
        if( maxNode == maxNode->father->right){
            maxNode->father->right = newNode;
        }else{
            maxNode->father->left = newNode;
        }

        //make the tree balance again
        if(maxNode->color == BLACK){
            newNode->color = BLACK_BLACK;
            balance(newNode->father);
        }

        //release space
        delete maxNode;
        return true;

    }

    else{

        if(node == root){
            root->key = root->pos = -1;
            return true;
        }

        //when reach here, node must be a leaf node and has father
        node* newNode = new Node;
            
        //update father and child relationship
        if(node->father->right == node){
            node->father->right = newNode;
        }else{
            node->father->left = newNode;
        }

        if(node->color == BLACK){
            newNode->color = BLACK_BLACK;
            balance(newNode->father);
        }

        delete node;
        return true;
    }
}





//old version: 
bool RBTree::remove(int key){
    Node* removeNode = fetch(key);

	//delete comments
	print(removeNode);
	cout << "RBTree.cpp line206" << endl;

    if( removeNode == NULL )
        return false;

	if (removeNode->pos == -1)
		return false;

    Node* leftNode = removeNode->getLeft();
    Node* rightNode = removeNode->getRight();

    if( leftNode != NULL ){
        int flag = 0;
        /* try to get the largest Node in left subtree */
        Node* tempNode = leftNode;

        while(!flag){
            flag = ( tempNode->getRight() == NULL ) ? 1 : 0;
            tempNode = ( flag ) ? tempNode : tempNode->getRight();
        }

        /* update deleteNode */
       // deleteNode[removeNode->getKey()] = removeNode->getPos();

        removeNode->setPos( tempNode->getPos() );

        if(tempNode->getColor() == RED){
            tempNode->getFather()->setRight(new Node);
            /* release space */
            delete tempNode;
        }
            /* the largest Node in left subtree is a BLACK node */
        else{
            if( tempNode->getLeft() == NULL ){

                /* tempNode's father has a double black right child */
                /* balance the tree */
                /* using nephew */

                cout << "tempNode's left child is Double Black Child!" << endl;
                cout << "unfinished!" << endl;

                /* 
                Node* fatherNode = tempNode->getFather();
                deleteNode[ tempNode->getKey() ] = tempNode->getPos();
                delete tempNode;

                fatherNode->setRight( NULL );
                balance( fatherNode );//fatherNode is double black
                */

            }
            /* fortunately tempNode's left child must be a RED node */
            else{
                
                tempNode->setPos( tempNode->getLeft()->getPos() );
                delete tempNode->getLeft();
                tempNode->setLeft(new Node);
            }
        }
    }else if( rightNode != NULL ){
        int flag = 0;
        /* find the smallest node in right subtree */
        Node* tempNode = rightNode;

        while( !flag ){
            flag = ( tempNode->getLeft() == NULL ) ? 1 : 0;
            tempNode = ( flag ) ? tempNode : tempNode->getLeft();
        }

     //   deleteNode[ removeNode->getKey() ] = removeNode->getPos();

        
        removeNode->setPos( tempNode->getPos() );

        if( tempNode->getColor() == RED ){
            tempNode->getFather()->setLeft(new Node);
        }else{
            /* tempNode is a BLACK node */
            if( tempNode->getRight() == NULL ){
                cout << "tempNode's right child is a double DOUBLE BLACK child!" << endl;
                cout << "Unfinished!" << endl;
                /*
                Node* fatherNode = tempNode->getFather();
                deleteNode[ tempNode->getKey() ] = tempNode->getPos();
                delete tempNode();

                fatherNode()->setLeft(NULL);
                balance( fatherNode );//fatherNode is double black
                */
            }
        }
    }else{
        /* tempNode has no child */
        if( removeNode->getColor() == RED ){

			//delete comments
			cout << "Node to be removed is RED Node" << endl;
			cout << "RBTree.cpp  line 310" << endl;


       //     deleteNode[removeNode->getKey() ] = removeNode->getPos();

            Node* fatherNode = removeNode->getFather();

            if( fatherNode->getRight() == removeNode){
                fatherNode->setRight(new Node);
				delete removeNode;
            }else{
                fatherNode->setLeft(new Node);
				delete removeNode;
            }

        }else{
            /* tempNode is a BLACK node */

            Node* fatherNode = removeNode->getFather();

			if (fatherNode == NULL) {
				/* node to be removes is root*/
				delete root;
				root = new Node;
				return true;
			}

            if( fatherNode->getRight() == removeNode){
                fatherNode->setRight(new Node);
             //   balance( fatherNode );//fatherNode left child is black, right child is NULL
            }else{
                fatherNode->setLeft(new Node);
            //    balance( fatherNode );//fatherNode right chils is black, left child is NULL
            }
            
    //        deleteNode[removeNode->getKey() ] = removeNode->getPos();
			delete removeNode;

        }
    }

    return true;
}