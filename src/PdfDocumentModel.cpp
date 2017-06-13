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

    for (int page = 0; page < _doc->numPages(); page++) {
        _pages[page] = _doc->page(page);

        foreach(Poppler::TextBox* const textBox, _pages[page]->textList()) {
            int x = textBox->boundingBox().x();
            int y = textBox->boundingBox().y();
            _pdfExtract.addText(page, x, y, textBox->text());
             delete textBox;
        }
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
    _pdfExtract.clear();
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
    roles[RoleNames::RawRole] = "raw";
    return roles;
}

QVariant PdfDocumentModel::data(const QModelIndex &index, int role) const
{
    int page = index.row();
    if (page < 0 || page >= _pages.keys().count()) {
        qDebug() << "ERROR: no such page" << page;
        return QVariant();
    }
    if (role == RoleNames::UrlRole) {
        return QString("image://pdf/") + _fileName + "/" + QString::number(page);
    }
    else if (role == RoleNames::RawRole) {
        return _pdfExtract.pageText(page);
    }
    qDebug() << "ERROR: no such role:" << role;
    return QVariant();
}

QImage PdfDocumentModel::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int row = id.split("/").last().toInt();
    if (row < 0 || row >= _pages.keys().count()) {
        qDebug() << "ERROR: no such page" << row;
        return QImage();
    }

    QImage image = _pages[row]->renderToImage(90, 90, -1, -1,
                                              requestedSize.width() > 0 ? requestedSize.width() : -1,
                                              requestedSize.height() > 0 ? requestedSize.height() : -1);
    if (size) {
        *size = _pages[row]->pageSize();
    }
    return image;
}
