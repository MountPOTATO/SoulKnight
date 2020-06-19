#include "Entity/Enemy/Ranger.h"

bool Ranger::init() {
	Sprite* sprite = Sprite::create("Enemy\\Ranger.png");
	this->bindSprite(sprite);
	setAnchorPoint(Point(0.5f, 0.5f));
	setSpeed(RANGER_SPEED);
	setHP(RANGER_HP);
	isAiMoving = false;

	this->isActivated = true;
	this->getSprite()->setVisible(true);//����Ծ�Ĺ����Ȳ���ʾ
	this->scheduleUpdate();//�������������Ӱ��֡���Ϳ��Ƿŵ������Ծʱ������

	return true;
}

 int Ranger::attack() {
	 
}

 void Ranger::calDistance() {
	 if (isAiMoving == true) { return; }//�������ִ����һ���ƶ�ָ��Ͳ�Ҫ�ظ��ƶ���
	 auto dir = (int)(8 * CCRANDOM_0_1());//�������0-7
	 log("%f", dir);
	 switch (dir)
	 {
	 case 0:
		 nextMovingDir = left;
		 break;
	 case 1:
		 nextMovingDir = upLeft; 
		 break;
	 case 2:
		 nextMovingDir = up; 
		 break;
	 case 3:
		 nextMovingDir = upRight; 
		 break;
	 case 4:
		 nextMovingDir = right; 
		 break;
	 case 5:
		 nextMovingDir = downRight;
		 break;
	 case 6:
		 nextMovingDir = down;
		 break;
	 case 7:
		 nextMovingDir = downLeft;
		 break;
	 }//�����Ӧ�İ���

	 nextMovingDistance = (int)(RANGER_MAX_MOVES_ROUND * CCRANDOM_0_1() + 1);//���ɽ���1-3������


 }

 void Ranger::update(float delta) {
	 //�ƶ� 
	 auto curPos = this->getPosition();
	 this->calDistance();
	 if (remainMovingDistance > 0) {
		 isAiMoving = true;//�����ƶ�ģʽ
		//����һ���ƶ�
		 remainMovingDistance -= 1;
		 //����ƶ�·���Ƿ񱻵�ס
		 auto dstPos = Point(0, 0);//���������һ����
		 //������յ�
		 switch (nextMovingDir)
		 {
		 case left:
			 dstPos = curPos + Point(-RANGER_SPEED, 0);
			 break;
		 case upLeft:
			 dstPos = curPos + Point(-RANGER_SPEED / 1.414, RANGER_SPEED / 1.414);
			 break;
		 case up:
			 dstPos = curPos + Point(0, RANGER_SPEED);
			 break;
		 case upRight:
			 dstPos = curPos + Point(RANGER_SPEED / 1.414, RANGER_SPEED / 1.414);
			 break;
		 case right:
			 dstPos = curPos + Point(RANGER_SPEED, 0);
			 break;
		 case downRight:
			 dstPos = curPos + Point(RANGER_SPEED / 1.414, -RANGER_SPEED / 1.414);
			 break;
		 case down:
			 dstPos = curPos + Point(0, -RANGER_SPEED);
			 break;
		 case downLeft:
			 dstPos = curPos + Point(-RANGER_SPEED / 1.414, -RANGER_SPEED / 1.414);
			 break;
		 default:
			 break;
		 }
		 auto x = dstPos.x;
		 auto y = dstPos.y;
		 if (isPosBlocked(Point(x + halfOfHitBox, y + halfOfHitBox))) { isAiMoving = false; return; }
		 if (isPosBlocked(Point(x + halfOfHitBox, y - halfOfHitBox))) { isAiMoving = false; return; }
		 if (isPosBlocked(Point(x - halfOfHitBox, y + halfOfHitBox))) { isAiMoving = false; return; }
		 if (isPosBlocked(Point(x - halfOfHitBox, y - halfOfHitBox))) { isAiMoving = false; return; }//�ƶ�·�����赲�� �����ж�
		 auto pos = tileCoordForPosition(curPos);
		 auto mapSize = m_map->getMapSize();

		 this->setPositionZ(pos.y - mapSize.height);

		 Entity::setTagPosition(x, y);
	 }
	 if (remainMovingDistance == 0) { isAiMoving = false; remainMovingDistance = RANGER_MAX_MOVES_ROUND; }
	 return;



	 //����
	 //�����ǲ����ƺ��Ѿ�д��helloworld����
 }

 bool Ranger::isPosBlocked(Point dstPos) {

	 //��ȱ*/
	 Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));

	 int tiledGid = meta->getTileGIDAt(tiledPos);//��ȡ������ӵ�Ψһ��ʶ



	 //�ж���������Ƿ����
	 if (tiledGid != 0) {

		 auto propMap = m_map->getPropertiesForGID(tiledGid).asValueMap();




		 if (propMap.find("Collidable") != propMap.end()) {
			 //��ȡ���ӵ�Collidable����
			 Value prop = propMap.at("Collidable");
			 if (prop.asString().compare("true") == 0) {
				 //���������������Ϊtrue��������Ҽ����ƶ�
				 return true;
			 }
		 }

	 }
	 return false;//��֮������false
 }