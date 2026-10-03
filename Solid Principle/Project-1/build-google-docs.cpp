#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Abstraction for document elements
class DocumentElements
{
public:
    virtual string render() = 0;
};

// Concrete implementation for text elements
class TextElement : public DocumentElements
{
private:
    string text;

public:
    TextElement(string text)
    {
        this->text = text;
    }

    string render() override
    {
        return text;
    }
};

// Concrete implementation for Image elements
class ImageElement : public DocumentElements
{
private:
    string imagePath;

public:
    ImageElement(string imagePath)
    {
        this->imagePath = imagePath;
    }

    string render() override
    {
        return "[Image: " + imagePath + "]";
    }
};

// NewLineElement represent a line break in the document
class NewLineElement : public DocumentElements
{
public:
    string render() override
    {
        return "\n";
    }
};

// TabSpaceElement represents a tab space in the document.
class TabSpaceElement : public DocumentElements
{
public:
    string render() override
    {
        return "\t";
    }
};

// Document class responsible for holding the collection of elements
class Document
{
private:
    vector<DocumentElements *> documentElements;

public:
    void addElement(DocumentElements *element)
    {
        documentElements.push_back(element);
    }

    // Render the document by concatenating the render output of all elements.
    string render()
    {
        string result;
        for (auto element : documentElements)
        {
            result += element->render();
        }
        return result;
    }
};

// Persistence abstraction
class Persistence
{
public:
    virtual void save(string data) = 0;
};

// File Storage Implementation of Persistence
class FileStorage : public Persistence
{
public:
    void save(string data) override
    {
        ofstream outFile("document.txt");
        if (outFile)
        {
            outFile << data;
            outFile.close();
            cout << "Document saved to document.txt" << endl;
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

// Placeholder DBStorage implementation
class DBStorage : public Persistence
{
public:
    void save(string data) override
    {
        // Save to DB
    }
};

// DocumentEditor class managing cilent interactions
class DocumentEditor
{
private:
    Document *document;
    Persistence *storage;
    string renderedDocument;

public:
    DocumentEditor(Document *document, Persistence *storage)
    {
        this->document = document;
        this->storage = storage;
    }

    void addText(string text)
    {
        document->addElement(new TextElement(text));
    }

    void addImage(string imagePath)
    {
        document->addElement(new ImageElement(imagePath));
    }

    // Adds a new line to the document
    void addNewLine()
    {
        document->addElement(new NewLineElement());
    }

    // Adds a tab space to the document.
    void addTabSpace()
    {
        document->addElement(new TabSpaceElement());
    }

    string renderDocument()
    {
        if (renderedDocument.empty())
        {
            renderedDocument = document->render();
        }
        return renderedDocument;
    }

    void saveDocument()
    {
        storage->save(renderDocument());
    }
};

// cilent usage example

int main()
{

    Document *document = new Document();
    Persistence *persistence = new FileStorage();

    DocumentEditor *editor = new DocumentEditor(document, persistence);

    // Stimulate a cilent using the editor with common text formatting features.
    editor->addText("Hello, World");
    editor->addNewLine();
    editor->addText("This is a real world document editor example");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Idented text after the tab space");
    editor->addNewLine();
    editor->addImage("picture.jpg");

    // Render and Display the final document.
    cout << editor->renderDocument() << endl;

    editor->saveDocument();

    return 0;
}