#pragma once
#include <QImage>
#include <QString>

class ResourceManager {
public:
    static ResourceManager& instance();
    
    const QImage& headImage() const;
    const QImage& bodyImage() const;
    const QImage& foodImage() const;

private:
    ResourceManager();
    QImage loadImage(const QString& path) const;

    QImage m_head;
    QImage m_body;
    QImage m_food;
};