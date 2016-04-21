//
// Created by 王鹏飞 on 16/4/18.
//

#ifndef FRAMENET_EN_DP_TREE_H
#define FRAMENET_EN_DP_TREE_H

#include <map>

class dp_Node{
public:
    std::string value;
    std::string pos;
    int parent;
    std::string dependency;
    bool is_lu;
    bool is_fe;

    dp_Node(string value,string pos,int parent,string dependency){
        this->value=value;
        this->pos=pos;
        this->parent=parent;
        this->dependency=dependency;
    }

    inline bool operator == (const dp_Node &dp) const{
        return (value==dp.value)&&(pos==dp.pos)&&(parent==dp.parent)&&(dependency==dp.dependency);
    }
};

class dp_Tree {
public:
    //member
    std::vector<dp_Node>nodes;

    std::map<int,std::vector<int>> children_array;


    //function
    std::vector<dp_Node>get_path_to_root(dp_Node node);

    std::vector<dp_Node> get_path_between_node(dp_Node from,dp_Node to);

    void set_children_array();

    void conflat_node();

    std::vector<dp_Node>dp_Tree::get_template_path(std::vector<std::string>);
};


#endif //FRAMENET_EN_DP_TREE_H
