//
// Created by 王鹏飞 on 16/4/13.
//
#include "builder.h"

FrameNetBuilder::FrameNetBuilder(std::string frames_path, std::string relations_file_path, std::string lu_path) {
    this->frames_path=frames_path;
    this->relation_file_path=relations_file_path;
    this->lu_path=lu_path;
}


FrameNet FrameNetBuilder::read(){
    FrameNet fn = FrameNet();
    for(auto filename:listdir(frames_path)){
        std::string path=frames_path+filename;
        Frame *frame = frame_builder.build_frame(path);
        fn.add_frame(frame);
    }
    this->read_relations(fn);
    return fn;
}


void FrameNetBuilder::read_relations(FrameNet &fn){

    rapidxml::file<> fdoc(this->relation_file_path);
    rapidxml::xml_document<> doc;
    doc.parse<0>(fdoc.data());

    rapidxml::xml_node<>* root = doc.first_node();
    for(auto fr_type = root->first_node("frameRelationType");fr_type!= nullptr;fr_type = fr_type->next_sibling()){
        std::string fr_type_name = fr_type->first_attribute("name")->value();
        for(auto fr = fr_type->first_node("frameRelation");fr!= nullptr;fr = fr->next_sibling()){
            std::string subFrame = fr->first_attribute("subFrameName")->value();
            std::string superFrame = fr->first_attribute("superFrameName")->value();
            Frame *current_frame = fn.get_frame(subFrame);
            if(fr_type_name == "Causative_of"||fr_type_name == "Inchoative_of"||fr_type_name == "Precedes"){
                current_frame = fn.get_frame(superFrame);
            }

            for(auto fe_r =fr->first_node("FERelation");fe_r!= nullptr;fe_r = fe_r->next_sibling()){
                std::string parent = fe_r->first_attribute("superFEName")->value();
                std::string child = fe_r->first_attribute("subFEName")->value();
                FrameElementRelation *fr = new FrameElementRelation(parent,child,fr_type_name,superFrame,subFrame);
                current_frame->add_fe_relation(fr);

            }

        }
    }
}

std::vector<std::string> FrameNetBuilder::listdir(std::string path){

    std::vector<std::string> listnames;
    DIR           *d;
    struct dirent *dir;
    d = opendir(frames_path);
    if(d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_name[0] == '.')
                continue;
            listnames.push_back(dir->d_name);
        }
        closedir(d);
    }
    return listnames;
}
void FrameNetBuilder::build_lus_for_frame(std::string frame_name, FrameNet fn) {
    Frame * frame = fn.get_frame(frame_name);
    if(frame->get_lexicalUnits().size() <= 0){
        std::cout<<"No lexical units for frame.";
    }
    else{
        for(auto p_unit :frame->get_lexicalUnits()){
            if(p_unit->get_status() != "Problem"){
                int ID = p_unit->get_ID();
                std::string path = this->lu_path+"lu"+std::to_string(ID)+".xml";
                LexicalUnit* lu = parse_lu_xml(path,p_unit);
                fill_annotations(lu);
                frame->add_fe_realizations(lu->get_fe_realizations());
            }
        }
    }
}


void FrameNetBuilder::fill_annotations(LexicalUnit *lu){
    for(auto fe_r:lu->get_fe_realizations()){
        for(auto anno:lu->get_annotations()){
            if(std::find(fe_r->annotationID.begin(),fe_r->annotationID.end(),anno->get_ID()) != fe_r->annotationID.end()){
                fe_r->annotations.push_back(anno);
            }
        }
    }
}

LexicalUnit*  FrameNetBuilder::parse_lu_xml(std::string xml_path,LexicalUnit* original){
    rapidxml::file<> fdoc(this->relation_file_path);
    rapidxml::xml_document<> doc;
    doc.parse<0>(fdoc.data());

    rapidxml::xml_node<>* root = doc.first_node();

    std::string name = original->get_name(); //带有词性
    std::string POS = original->get_pos();
    std::string frame_name = original->get_frame_name();
    int ID = original->get_ID();
    std::string status = original->get_status();

    //std::string lexeme = root->first_node("lexeme")->first_attribute("name")->value();
    std::string definition = root->first_node("definition")->value();
    rapidxml::xml_node<>* valence = root->first_node("valences");
    std::vector<FERealization*>fe_realizations;
    for(auto p = valence->first_node("FERealization");p !=  nullptr;p = p->next_sibling()){
        fe_realizations.push_back(build_realization(p,frame_name,name));
    }

    std::vector<Annotation*> annotations;
    for(auto subCorpus = root->first_node("subCorpus");subCorpus != nullptr;subCorpus = subCorpus->next_sibling()){
        for(auto senten = subCorpus->first_node("sentence");senten != nullptr; senten = senten->next_sibling()){
            annotations.push_back(build_annotation(senten));
        }
    }

    original->set_definition(definition);
    original->set_fe_realizations(fe_realizations);
    original->set_annotations(annotations);
    return original;

}

FERealization* FrameNetBuilder::build_realization(rapidxml::xml_node<>* node,std::string frame_name,std::string lu_name){
    int total = atoi(node->first_attribute("total")->value());
    FERealization* fe_realization = new FERealization(frame_name,total,lu_name);
    std::string fe_name = node->first_node("FE")->first_attribute("name")->value();
    fe_realization->set_fe(fe_name);
    for(auto p_pattern = node->first_node("pattern");p_pattern != nullptr;p_pattern = p_pattern->next_sibling()){
        for(auto p_anno = p_pattern->first_node("annoSet");p_anno != nullptr; p_anno = p_anno->next_sibling() ){
            fe_realization->set_annotationID(atoi(p_anno->first_attribute("ID")->value()));
        }
    }
    return fe_realization;
}


Annotation* FrameNetBuilder::build_annotation(rapidxml::xml_node<>* senten){

    std::string text = senten->first_node("text")->value();
    for(auto annoset = senten->first_node("annotationSet");annoset != nullptr;annoset = annoset->next_sibling()){
        std::string status = annoset->first_attribute("status")->value();
        if(status == "MANUAL"||status == "AUTO_EDITED"){
            int ID = atoi(annoset->first_attribute("ID")->value());
            std::vector<Label> labels;

            for(auto layer = annoset->first_node("layer");layer != nullptr;layer = layer->next_sibling()){
                std::string ly_name = layer->first_attribute("name")->value();

                if(ly_name == "FE"){
                    for(auto label = layer->first_node("label");label != nullptr;label = label->next_sibling()){
                        int start = std::stoi(label->first_attribute("start")->value());
                        int end = std::stoi(label->first_attribute("end")->value());
                        std::string fe_name = label->first_attribute("name")->value();
                        int fe_ID = std::stoi(label->first_attribute("feID")->value());

                        labels.push_back({start,end,fe_name,fe_ID});
                    }
                }
                if(ly_name == "Target"){
                    for(auto label = layer->first_node("label");label != nullptr;label = label->next_sibling()){
                        int start = std::stoi(label->first_attribute("start")->value());
                        int end = std::stoi(label->first_attribute("end")->value());
                        std::string fe_name = "Target";
                        int fe_ID = -1;
                        labels.push_back({start,end,fe_name,fe_ID});
                    }
                }
            }
            Annotation *annotation = new Annotation(text,ID,status,labels);
            return annotation;
        }
    }
}





