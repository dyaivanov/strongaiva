#ifndef SKELETONEXTRACTOR_H
#define SKELETONEXTRACTOR_H

#include <QDebug>
#include <QList>
#include <QString>
#include <iostream>

#include <openpose/headers.hpp>

#include "Skeleton.h"

using namespace std;

class SkeletonExtractor {

public:
    SkeletonExtractor();
    static void createFromOpenpose(std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>&, float wk, float hk, vector<Skeleton> &_vs);
};

#endif // SKELETONEXTRACTOR_H
