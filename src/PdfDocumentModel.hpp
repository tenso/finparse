#ifndef PDFDOCUMENTMODEL_HPP
#define PDFDOCUMENTMODEL_HPP

#include <QAbstractListModel>
#include <QQuickImageProvider>
#include <poppler/qt5/poppler-qt5.h>

#include "PdfExtract.hpp"

class PdfDocumentModel : public QAbstractListModel, public QQuickImageProvider
{
    Q_OBJECT
public:
    explicit PdfDocumentModel(QObject *parent = nullptr);
    virtual ~PdfDocumentModel();

    enum RoleNames {
        UrlRole = Qt::UserRole + 1,
        RawRole
    };

signals:

public slots:
    void load(const QString& fileName);
    void free();
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

private:
    QString _fileName;
    Poppler::Document* _doc;
    QHash<int, Poppler::Page*> _pages;
    PdfExtract _pdfExtract;
};

#endif // PDFDOCUMENTMODEL_HPP
