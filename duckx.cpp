#include "duckx.hpp"

void duckx::Run::setParent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:r");
}

const pugi::char_t *duckx::Run::text() {
    return this->current.child("w:t").text().get();
}

const duckx::Run& duckx::Run::next() {
    this->current = this->current.next_sibling();
    return *this;
}

bool duckx::Run::hasNext() {
    return this->current != 0;
}

duckx::Paragraph::Paragraph() {}

void duckx::Paragraph::setParent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:p");
    
    this->run.setParent(
        this->current
    );
}

const duckx::Paragraph &duckx::Paragraph::next() {
    this->current = this->current.next_sibling();
    this->run.setParent(this->current);
    return *this;
}

bool duckx::Paragraph::hasNext() {
    return this->current != 0;
}

duckx::Run &duckx::Paragraph::runs() {
    return this->run;
}


duckx::Document::Document() {
    // TODO: this function must be removed!
    this->directory = "";
}

duckx::Document::Document(std::string directory) {
    this->directory = directory;
}

void duckx::Document::file(std::string directory) {
    this->directory = directory;
}

void duckx::Document::open() {
    Handle handle(this->directory);

    document.load_string(
        handle.getContent()
    );

    this->paragraph.setParent(
        document.child("w:document").child("w:body")
    );
}

void duckx::Document::save() {
    this->document.save_file("document.xml");

    Handle handle(this->directory);
    handle.replaceFile("document.xml");

    remove("document.xml");
}

duckx::Paragraph &duckx::Document::paragraphs() {
    return this->paragraph;
}