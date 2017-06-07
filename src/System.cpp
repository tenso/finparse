#include "System.hpp"
#include <QDebug>

System::System(QObject *parent) : QObject(parent)
{
    _pdfModel = new PdfDocumentModel(this);
    loadFiles(QList<QUrl>() << QUrl("doc/test1.pdf"));
}

System::~System()
{
}

void System::loadFiles(const QList<QUrl> &filenames)
{
    qDebug() << "load:" << filenames.at(0).path();
    _pdfModel->load(filenames.at(0).path());

    /*Poppler::Document* doc = Poppler::Document::load();
    for (int i = 0; i < doc->numPages(); i++) {
        Poppler::Page* page  = doc->page(i);
        foreach(Poppler::TextBox* const textBox, page->textList()) {
            qDebug() << textBox->boundingBox() << textBox->text();
        }
    }*/
}

PdfDocumentModel *System::model()
{
    return _pdfModel;
}
