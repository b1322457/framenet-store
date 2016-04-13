#include <iostream>
#include "src/rapidxml/rapidxml.hpp"
#include "src/rapidxml/rapidxml_utils.hpp"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
using  namespace rapidxml;
using  namespace boost::algorithm;
int main() {


    rapidxml::file<> fdoc("/Users/wangpf/Downloads/fndata-1.6/frRelation.xml");
    rapidxml::xml_document<> doc;
    doc.parse<0>(fdoc.data());

    rapidxml::xml_node<>* root = doc.first_node();


    for(auto node = root->first_node("frameRelationType");node!= nullptr;node = node->next_sibling()){
        std::cout<<node->first_attribute("name")->value()<<std::endl;
    }

    //std::cout<<root->first_attribute("ID")->value()<<std::endl;

   // rapidxml::xml_node<>* node1 = root->first_node();
    //std::cout<<node1->name()<<std::endl;
    //std::cout<<node1->value()<<std::endl;

   // std::string s{node1->value()};
   // boost::regex expr{"<[^>]*>"};
   // std::string fmt{""};
   // std::cout << boost::regex_replace(s, expr, fmt) << '\n';

    //rapidxml::xml_node<>* node2 = node1->first_node();
    //std::cout<<node2->name()<<std::endl;
    //std::cout<<node2->value()<<std::endl;

    //rapidxml::xml_node<>* node3 = node1->first_node();
    //std::cout<<node3->name()<<std::endl;
    //std::cout<<node3->value()<<std::endl;

    return 0;
}