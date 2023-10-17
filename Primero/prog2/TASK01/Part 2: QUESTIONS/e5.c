STATUS node_copy(const Node* nSource, Node* nDest){

	if(nSource == NULL){
		return ERROR;
	}

	if(nDest == NULL){
		nSource = node_init();
	}
	if(nDest == NULL){
		return ERROR;
	}

	if(node_setId(nDest, nSource) == ERROR){
		return ERROR;
	}
	if(node_setName(nDest, nSource) == ERROR){
		return ERROR;
	}
	if(node_setNConnect(nDest, nSource) == ERROR){
		return ERROR;
	}
	if(node_setLabel(nDest, nSource) == ERROR){
		return ERROR;
	}

	return OK;
}


STATUS node_copy(const Node* nSource, Node** nDest) wouldn't be valid because nDest would be a pointer type Node*, not Node**