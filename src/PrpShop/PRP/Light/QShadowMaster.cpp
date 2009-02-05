#include "QShadowMaster.h"

#include <QGroupBox>
#include <QLabel>
#include <QGridLayout>
#include "../../QKeyDialog.h"
#include "../../Main.h"

QShadowMaster::QShadowMaster(plCreatable* pCre, QWidget* parent)
             : QCreatable(pCre, pCre->ClassIndex(), parent)
{
    plShadowMaster* obj = (plShadowMaster*)fCreatable;

    fOwnerLink = new QCreatableLink(this);
    fOwnerLink->setText(tr("Owner Object"));
    fOwnerLink->setKey(obj->getOwner());

    fSynchObjLink = new QCreatableLink(this, false);
    fSynchObjLink->setText(tr("Synch Flags"));
    fSynchObjLink->setCreatable(obj);
    fSynchObjLink->setForceType(kSynchedObject);

    QGroupBox* grpProps = new QGroupBox(tr("Properties"), this);
    QGridLayout* layProps = new QGridLayout(grpProps);
    layProps->setVerticalSpacing(0);
    fProperties[plShadowMaster::kDisable] = new QCheckBox(tr("Disable"), grpProps);
    fProperties[plShadowMaster::kSelfShadow] = new QCheckBox(tr("Self Shadow"), grpProps);
    layProps->addWidget(fProperties[plShadowMaster::kDisable], 0, 0);
    layProps->addWidget(fProperties[plShadowMaster::kSelfShadow], 0, 1);
    for (size_t i=0; i<plShadowMaster::kNumProps; i++)
        fProperties[i]->setChecked(obj->getProperty(i));

    fMinDist = new QDoubleSpinBox(this);
    fMinDist->setRange(-2147483648.0, 2147483647.0);
    fMinDist->setDecimals(3);
    fMinDist->setSingleStep(0.1);
    fMinDist->setValue(obj->getMinDist());

    fMaxDist = new QDoubleSpinBox(this);
    fMaxDist->setRange(-2147483648.0, 2147483647.0);
    fMaxDist->setDecimals(3);
    fMaxDist->setSingleStep(0.1);
    fMaxDist->setValue(obj->getMaxDist());

    fMinSize = new QSpinBox(this);
    fMinSize->setRange(0, 0x7FFFFFFF);
    fMinSize->setValue(obj->getMinSize());

    fMaxSize = new QSpinBox(this);
    fMaxSize->setRange(0, 0x7FFFFFFF);
    fMaxSize->setValue(obj->getMaxSize());

    fAttenDist = new QDoubleSpinBox(this);
    fAttenDist->setRange(-2147483648.0, 2147483647.0);
    fAttenDist->setDecimals(3);
    fAttenDist->setSingleStep(0.1);
    fAttenDist->setValue(obj->getAttenDist());

    fPower = new QDoubleSpinBox(this);
    fPower->setRange(-2147483648.0, 2147483647.0);
    fPower->setDecimals(3);
    fPower->setSingleStep(0.1);
    fPower->setValue(obj->getPower());

    QGridLayout* layout = new QGridLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->addWidget(fOwnerLink, 0, 0, 1, 3);
    layout->addWidget(fSynchObjLink, 1, 0, 1, 3);
    layout->addWidget(grpProps, 2, 0, 1, 3);
    layout->addWidget(new QLabel(tr("Min"), this), 3, 1);
    layout->addWidget(new QLabel(tr("Max"), this), 3, 2);
    layout->addWidget(new QLabel(tr("Distance:"), this), 4, 0);
    layout->addWidget(fMinDist, 4, 1);
    layout->addWidget(fMaxDist, 4, 2);
    layout->addWidget(new QLabel(tr("Size:"), this), 5, 0);
    layout->addWidget(fMinSize, 5, 1);
    layout->addWidget(fMaxSize, 5, 2);
    layout->addWidget(new QLabel(tr("Attensity Dist:"), this), 6, 0);
    layout->addWidget(fAttenDist, 6, 1, 1, 2);
    layout->addWidget(new QLabel(tr("Power:"), this), 7, 0);
    layout->addWidget(fPower, 7, 1, 1, 2);

    connect(fOwnerLink, SIGNAL(addObject()), this, SLOT(setOwner()));
    connect(fOwnerLink, SIGNAL(delObject()), this, SLOT(unsetOwner()));
}

void QShadowMaster::saveDamage()
{
    plShadowMaster* obj = (plShadowMaster*)fCreatable;

    for (size_t i=0; i<plShadowMaster::kNumProps; i++)
        obj->setProperty(i, fProperties[i]->isChecked());
    obj->setAttenDist(fAttenDist->value());
    obj->setDist(fMinDist->value(), fMaxDist->value());
    obj->setSize(fMinSize->value(), fMaxSize->value());
    obj->setPower(fPower->value());
}

void QShadowMaster::setOwner()
{
    plShadowMaster* obj = (plShadowMaster*)fCreatable;
    QFindKeyDialog dlg(this);
    if (obj->getOwner().Exists())
        dlg.init(PrpShopMain::ResManager(), obj->getOwner());
    else
        dlg.init(PrpShopMain::ResManager(), obj->getKey()->getLocation(), kSceneObject);
    if (dlg.exec() == QDialog::Accepted) {
        obj->setOwner(dlg.selection());
        fOwnerLink->setKey(obj->getOwner());
    }
}

void QShadowMaster::unsetOwner()
{
    plShadowMaster* obj = (plShadowMaster*)fCreatable;
    obj->setOwner(plKey());
    fOwnerLink->setCreatable(NULL);
}