void DirShow(Tree *ptree){
    TrnodeShow(ptree->root,0);
}

void TreeShow(Trnode *root,int depth){
    if(root==NULL)
        return;
    PrintName(root,depth);
    for(Trnode *cur=root;cur!=NULL;cur=cur->sibling)
        TreeShow(cur->child,depth+1);
}

void PrintName(Trnode *ptr,int depth){
    for(int i=0;i<depth;i++)
        putchar('\t');
    puts(ptr->data.dir);
}
