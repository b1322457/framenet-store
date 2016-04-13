//
// Created by 王鹏飞 on 16/4/6.
//

#ifndef FRAMENET_EN_BUILDER_H
#define FRAMENET_EN_BUILDER_H

#endif //FRAMENET_EN_BUILDER_H

#include <iostream>
#include <dirent.h>
#include <vector>
#include "framenet.h"



class FrameNetBuilder{
public:

    FrameNetBuilder(std::string frames_path,std::string relations_file_path,std::string lu_path);

    /**
     * Build FrameNet object
     */
    FrameNet read();

    /**
     * Build frame relation from frRelation.xml
     */
    void read_relations(FrameNet &fn);

    /**
     *  return list filenames of the dir
     */
    std::vector<std::string> listdir(std::string path);

    /**
     *  add detail lu infomation
     */
    void build_lus_for_frame(std::string frame_name,FrameNet fn);


    /**
     * fill fe_realization annotations according to their ID
     */
    void fill_annotations(LexicalUnit *lu);

    /**
     * read info from lu.xml;
     */
    LexicalUnit*  parse_lu_xml(std::string xml_path,LexicalUnit* original);


    /**
     * fe_realization:an fe with annotated sentences
     */
    FERealization* build_realization(rapidxml::xml_node<>* node,std::string frame_name,std::string lu_name);

    /**
     * annotation: a raw sentence with their semantic labels
     */
    Annotation* build_annotation(rapidxml::xml_node<>* senten);
private:
    std::string frames_path;
    std::string relation_file_path;
    std::string lu_path;
    FrameBuilder frame_builder = FrameBuilder();

};