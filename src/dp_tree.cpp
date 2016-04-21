//
// Created by 王鹏飞 on 16/4/18.
//

#include "dp_tree.h"

std::vector<dp_Node> dp_Tree::get_path_to_root(dp_Node node){
    std::vector<dp_Node>Path;
    while(node.parent!=-1){
        Path.push_back(node);
        node = nodes[node.parent];
    }
    Path.push_back(node);//push root node;
    return Path;
}

std::vector<dp_Node> dp_Tree::get_path_between_node(dp_Node from,dp_Node to){
    std::vector<dp_Node> path1 = get_path_to_root(from);
    std::vector<dp_Node> path2 = get_path_to_root(to);
    std::vector<dp_Node> path_between;
    for(auto it1 = path1.rbegin(),it2 = path2.rbegin();it1!=path1.rend()&&it2!=path2.rend();it1++,it2++){
        if(*it1!=*it2){
            auto ptr1 = it1.base();
            auto ptr2 = it2;
            for(auto i = path1.begin();i!=ptr1+1;i++)
            {
                path_between.push_back(*i);
            }
            for(auto j = ptr2;j!=path2.rend();j++){
                path_between.push_back(*j);
            }
            break;
        }
    }

    void dp_Tree::set_children_array(){
        for(int i=0;i<nodes.size();i++){
            if(nodes[i].parent!=-1){
                children_array[nodes[i].parent].push_back(i);
            }
        }
    }

    //如果该词是介词,并且孩子只有一个,将这个节点与其孩子节点
    void dp_Tree::conflat_node(){


        for(int i=0;i<nodes.size();i++){
            if(nodes[i].pos=="IN"){
                if(children_array[i].size()==1){
                    //children_array[i][0]:节点i孩子的index
                    int child_index = children_array[i][0];

                    //孩子index应该等于 节点i parent的index
                    nodes[child_index].parent = nodes[i].parent;

                    //关系是子节点的属性,关系变为这个介词的名称
                    nodes[child_index].dependency = nodes[i].value;

                    //删除nodes[i]的列表
                    //nodes[i].parent=
                    //nodes[i].value
                }
            }
        }
    }


    std::vector<std::vector<dp_Node>> dp_Tree::get_template_path(std::vector<std::string>lu_fe){
        dp_Node lu_node;
        std::vector<dp_Node> fe_nodes;
        std::vector<std::vector<dp_Node>>res_path;
        for(auto node:nodes){
            auto it = find(lu_fe.begin(),lu_fe.end(),node.value);
            if(it==lu_fe.begin()){
                node.is_lu=true;
                lu_node = node;
                continue;
            }
            if(it!=lu_fe.end()){
                node.is_fe=true;
                fe_nodes.push_back(node);
            }
        }

        for(auto fe_node:fe_nodes){
            res_path.push_back(get_path_between_node(fe_node,lu_node));
        }
        return res_path;
    }


}