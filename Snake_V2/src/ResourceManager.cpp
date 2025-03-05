#include "ResourceManager.h"

ResourceManager& ResourceManager::instance() {
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager() {
    m_head = loadImage(":/data/head.png");
    m_body = loadImage(":/data/dot.png");
    m_food = loadImage(":/data/apple.png");
}

QImage ResourceManager::loadImage(const QString& path) const {
    QImage img;
    if(!img.load(path)) {
        throw std::runtime_error("Failed to load image: " + path.toStdString());
    }
    return img;
}

const QImage& ResourceManager::headImage() const { return m_head; }
const QImage& ResourceManager::bodyImage() const { return m_body; }
const QImage& ResourceManager::foodImage() const { return m_food; }