#include "StatusBar.h"
#include "HelloWorldScene.h"

StatusBar* StatusBar::create(Point position, Character* hero, int color)
{
	StatusBar* statusbar = new(std::nothrow)StatusBar;
	if (statusbar && statusbar->init(position, hero,color))
	{
		statusbar->autorelease();
		return statusbar;
	}
	else
	{
		CC_SAFE_DELETE(statusbar);
		return NULL;
	}
}

bool StatusBar::init(Point position, Character* hero, int color)
{
	this->setPosition(position);
	theHero = hero;

<<<<<<< HEAD
	if (color == QHP)
=======
	if (color == HP)
>>>>>>> 5ee7058665984be474fea769690cefecb80807d2
	{
		Sprite* blankBar = Sprite::create("StatusBar/blankBar.png");
		blankBar->setPosition(0, 0);
		this->addChild(blankBar, 1);

		Sprite* hpBar = Sprite::create("StatusBar/hpBar.png");
		hpBar->setPosition(0, 0);
		hpBar->setTag(1);
		this->addChild(hpBar, 2);
		
		int hp = theHero->getHP();
		sprintf(str, "%d/%d", hp, KNIGHT_HP);
		std::string strs = str;

		statusLabel = Label::createWithSystemFont(str, "Arial", 50);
		statusLabel->setPosition(0, 0);
		this->addChild(statusLabel, 3);

		/*hpLabel->setString("456789");*/
		scale = hpBar->getContentSize().width / KNIGHT_HP;
	}
<<<<<<< HEAD
	else if (color == QARMOR)
=======
	else if (color == ARMOR)
>>>>>>> 5ee7058665984be474fea769690cefecb80807d2
	{
		Sprite* blankBar = Sprite::create("StatusBar/blankBar.png");
		blankBar->setPosition(0, 0);
		this->addChild(blankBar, 1);

		Sprite* armorBar = Sprite::create("StatusBar/armorBar.png");
		armorBar->setPosition(0, 0);
		armorBar->setTag(1);
		this->addChild(armorBar, 2);

		int armor = theHero->getArmor();
		sprintf(str, "%d/%d", armor, KNIGHT_ARMOR);
		std::string strs = str;

		statusLabel = Label::createWithSystemFont(str, "Arial", 50);
		statusLabel->setPosition(0, 0);
		this->addChild(statusLabel, 3);

		scale = armorBar->getContentSize().width / KNIGHT_ARMOR;
	}
	else
	{
		Sprite* blankBar = Sprite::create("StatusBar/blankBar.png");
		blankBar->setPosition(0, 0);
		this->addChild(blankBar, 1);

		Sprite* mpBar = Sprite::create("StatusBar/mpBar.png");
		mpBar->setPosition(0, 0);
		mpBar->setTag(1);
		this->addChild(mpBar, 2);

		int mp = theHero->getMP();
		sprintf(str, "%d/%d", mp, KNIGHT_MP);
		std::string strs = str;

		statusLabel = Label::createWithSystemFont(str, "Arial", 50);
		statusLabel->setPosition(0, 0);
		this->addChild(statusLabel, 3);

		scale = mpBar->getContentSize().width / KNIGHT_MP;
	}
	return true;
}

void StatusBar::updateStatusBar(int color)
{
<<<<<<< HEAD
	if (color == QHP)
=======
	if (color == HP)
>>>>>>> 5ee7058665984be474fea769690cefecb80807d2
	{
		int status = theHero->getHP();
		if (status > KNIGHT_HP)
		{
			return;
		}
		float rectWidth = status * scale;
		auto node = (Sprite*)this->getChildByTag(1);
		const CCPoint origin = node->getTextureRect().origin;
		const Rect rect = CCRectMake(origin.x, origin.y, rectWidth, node->getContentSize().height);

		int hp = theHero->getHP();
		sprintf(str, "%d/%d", hp, KNIGHT_HP);
		std::string strs = str;

		statusLabel->setString(strs);

		setStatusBar(rect);
	}
<<<<<<< HEAD
	else if (color == QARMOR)
=======
	else if (color == ARMOR)
>>>>>>> 5ee7058665984be474fea769690cefecb80807d2
	{
		int status = theHero->getArmor();
		if (status > KNIGHT_ARMOR)
		{
			return;
		}
		float rectWidth = status * scale;
		auto node = (Sprite*)this->getChildByTag(1);
		const CCPoint origin = node->getTextureRect().origin;
		const Rect rect = CCRectMake(origin.x, origin.y, rectWidth, node->getContentSize().height);
		
		int armor = theHero->getArmor();
		sprintf(str, "%d/%d", armor, KNIGHT_ARMOR);
		std::string strs = str;

		statusLabel->setString(strs);
		setStatusBar(rect);
	}
	else
	{
		int status = theHero->getMP();
		if (status > KNIGHT_MP)
		{
			return;
		}
		float rectWidth = status * scale;
		auto node = (Sprite*)this->getChildByTag(1);
		const CCPoint origin = node->getTextureRect().origin;
		const Rect rect = CCRectMake(origin.x, origin.y, rectWidth, node->getContentSize().height);

		int mp = theHero->getMP();
		sprintf(str, "%d/%d", mp, KNIGHT_MP);
		std::string strs = str;

		statusLabel->setString(strs);
		setStatusBar(rect);
	}
}

void StatusBar::setStatusBar(const CCRect& rect)
{
	auto node = (Sprite* )this->getChildByTag(1);
	node->setTextureRect(rect);
}