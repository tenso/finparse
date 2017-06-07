#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <QObject>
#include <QUrl>

#include "PdfDocumentModel.hpp"

class System : public QObject
{
    Q_OBJECT
public:
    explicit System(QObject *parent = nullptr);
    virtual ~System();

signals:

public slots:
    void loadFiles(const QList<QUrl> &filenames);
    PdfDocumentModel* model();

private:
    PdfDocumentModel* _pdfModel;
};

#endif // SYSTEM_HPP
