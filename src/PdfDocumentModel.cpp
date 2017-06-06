#include "PdfDocumentModel.hpp"
#include <QDebug>
#include <QImage>

PdfDocumentModel::PdfDocumentModel(QObject *parent)
    : QAbstractListModel(parent)
    , QQuickImageProvider(QQuickImageProvider::Image)
    , _doc(0)
{

}

PdfDocumentModel::~PdfDocumentModel()
{
    free();
}

void PdfDocumentModel::load(const QString &fileName)
{
    beginResetModel();
    free();
    _fileName = fileName;
    _doc = Poppler::Document::load(fileName);
    _doc->setRenderHint(Poppler::Document::TextAntialiasing);
    for (int i = 0; i < _doc->numPages(); i++) {
        _pages[i] = _doc->page(i);
    }
    endResetModel();
}

void PdfDocumentModel::free()
{
    if (_doc == 0) {
        return;
    }
    _fileName = "";
    foreach (int i, _pages.keys()) {
        delete _pages[i];
    }
    _pages.clear();
    delete _doc;
    _doc = 0;
}

int PdfDocumentModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return _pages.keys().count();
    }

    return 0;
}

QHash<int, QByteArray> PdfDocumentModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RoleNames::UrlRole] = "url";
    return roles;
}

QVariant PdfDocumentModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row >= _pages.keys().count()) {
        qDebug() << "ERROR: no such page" << row;
        return QVariant();
    }
    if (role != RoleNames::UrlRole) {
        qDebug() << "ERROR: no such role:" << role;
        return QVariant();
    }
    return QString("image://pdf/") + _fileName + "/" + QString::number(row);
}

QImage PdfDocumentModel::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int row = id.split("/").last().toInt();
    if (row < 0 || row >= _pages.keys().count()) {
        qDebug() << "ERROR: no such page" << row;
        return QImage();
    }
    //qDebug() << "req size" << requestedSize;
    //qDebug() << "page size:" << _pages[row]->pageSize();

    QImage image = _pages[row]->renderToImage(90, 90, -1, -1,
                                              requestedSize.width() > 0 ? requestedSize.width() : -1,
                                              requestedSize.height() > 0 ? requestedSize.height() : -1);
    if (size) {
        *size = _pages[row]->pageSize();
    }
    return image;
}
