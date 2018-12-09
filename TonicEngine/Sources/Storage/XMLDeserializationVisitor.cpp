#include <string>
#include "../../Headers/Storage/XMLDeserializationVisitor.h"

void XMLDeserializationVisitor::visit(const std::string &name, std::string &value) {

}

void XMLDeserializationVisitor::visit(const std::string &name, int &value) {

}

void XMLDeserializationVisitor::visit(const std::string &name, double &value) {

}

void XMLDeserializationVisitor::visit(const std::string &name, bool &value) {

}

void XMLDeserializationVisitor::visit(const std::string &name, SerializationReceiver &receiver) {

}

void XMLDeserializationVisitor::visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) {

}

void XMLDeserializationVisitor::visit(const std::string &name, std::vector<SerializationReceiver *> &receivers,
                                      std::function<SerializationReceiver *()> createFunc) {

}