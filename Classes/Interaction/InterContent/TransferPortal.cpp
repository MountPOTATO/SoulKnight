#include "TransferPortal.h"
#include "HelloWorldScene.h"

//Layer* TransferPortal::layer = Layer::create();
//
Scene* TransferPortal::createScene()
{
	auto scene = Scene::create();

	auto layer = TransferPortal::create();

    scene->addChild(layer);
	return scene;
}

bool TransferPortal::init()             //�Դ����Ŷ�̬Ч���ĳ�ʼ��
{
	auto transPor = Sprite::create("transferPortal1.png");
	Size sizeV = Director::getInstance()->getVisibleSize();
	transPor->setPosition(Vec2(sizeV.width / 2, sizeV.height/2));
	this->addChild(transPor);

	Size sizeC = transPor->getContentSize();
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame* > vTrans;
	for (int i = 1; i <= 3; i++)
	{
		char str[20] = { 0 };
		sprintf(str, "transferPortal%d.png", i);
		std::string strs = str;
		frame = SpriteFrame::create(strs, Rect(0, 0, sizeC.width,sizeC.height));
		vTrans.pushBack(frame);
	}

	log("si there any");

	Animation* rotate = Animation::createWithSpriteFrames(vTrans, 0.16f);
	Animate* action = Animate::create(rotate);
	transPor->runAction(RepeatForever::create(action));
	return true;
}

bool TransferPortal::isToPushScene()
{
	//���ִ����Ŷ����ǵ���ײ��⣬sprite����ײ��⣬�������л�
	//��⵽���ǵ���ײ���Ұ��°�ť ����г����л�
	//yΪ���� uΪ���� i�л�����
	//wasd��������
	//�����y���Ƿ񱻰���
	//Director::getInstance()->pushScene(�����������л�)
	return true;
}


bool TransferPortal::isColliedWithCharacter()
{
	//������ײ��⣻
	//����isToPushScene()����;
	return true;
}