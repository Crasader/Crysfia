#include "LayerCleaning.h"
#include "SceneBreeding.h"
USING_NS_CC;

namespace User
{
	LayerCleaning::LayerCleaning() :
		winSize(Director::getInstance()->getVisibleSize()),
		bottle(Sprite::create("res/texture/home/bottle_1.png")),
		mask(Sprite::create()),
		clippingNode(ClippingNode::create()),
		clippingShape(Sprite::create("res/texture/home/bottle_mask.png"))
	{
		bottle->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
		bottle->setScale(0.5f);
		this->addChild(bottle, 10);

		mask->setTextureRect(Rect(0, 0, winSize.width - 50, winSize.height - 350));
		mask->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.38f));
		mask->setColor(Color3B::BLACK);
		mask->setOpacity(128);

		clippingShape->setScale(0.5f);
		clippingShape->setPosition(winSize / 2);
		clippingNode->setStencil(clippingShape);
		clippingNode->setInverted(false);
		clippingNode->setAlphaThreshold(0.0f);

		clippingNode->addChild(mask, 20);
		this->addChild(clippingNode, 20);

		buttons.push_back(ui::Button::create("res/Image/WindowBase/WinBase_101.png"));
		buttons.push_back(ui::Button::create("res/Image/WindowBase/WinBase_107.png"));

		buttons[0]->setPosition(Vec2(winSize.width * 0.1f, winSize.height * 0.05f));
		buttons[1]->setPosition(Vec2(winSize.width * 0.9f, winSize.height * 0.05f));

		for (int i = 0; i < 2; i++) 
		{
			buttons[i]->setScale(0.7f);
			this->addChild(buttons[i], 30);
		}

	}

	LayerCleaning::~LayerCleaning()
	{

	}

	bool LayerCleaning::init()
	{
		if (!Layer::init()) { return false; }

		thisLocationTouchProcess();
		uiTouchProcess();		
		return true;
	}

	void LayerCleaning::thisLocationTouchProcess()
	{
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [=](Touch* touch, Event* event) {
			return true;
		};

		//�X���C�v����
		listener->onTouchMoved = [=](Touch* touch, Event* event) {

			//�r���ƃ^�b�`�����ꏊ�̂����蔻����Ƃ邽�߃^�b�`�����ʒu���擾
			auto location = touch->getLocation();

			//�P�t���[���O�̃^�b�`�ʒu�Ƃ̍������擾
			auto delta = touch->getDelta();

			//����X�AY�𑫂����l�̐�Βl���Ƃ肻�̒l���T�O���̂P�ɂ����l�ɂɐ�����������B
			//���̒l���g���ă}�X�N�̓��ߓx��������Ă���
			int creanVal = clampf((abs(delta.x + delta.y) * 0.05), 0, 2);

			//��������Ƃ��������蔻��Ɏg�����߂̋�`
			auto rect = Rect(mask->getPosition().x - mask->getContentSize().width / 2,
				mask->getPosition().y - mask->getContentSize().width / 2,
				mask->getContentSize().width,
				mask->getContentSize().height);

			if (5 < mask->getOpacity())
			{
				if (rect.containsPoint(location))
				{
					mask->setOpacity(mask->getOpacity() - creanVal);
					log("%d", mask->getOpacity());
				}
			}
			else if (mask->getOpacity() >= 0 && mask->getOpacity() <= 5)
			{
				  mask->setOpacity(0); 
			}
		};

		listener->onTouchEnded = [=](Touch* touch, Event* event) {
			mask->stopAllActions();
		};

		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	}

	//�|�����C���[���ł�UI����
	void LayerCleaning::uiTouchProcess()
	{
		//�߂�{�^��
		buttons[0]->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				
			}
		});
	}

	void LayerCleaning::hoge()
	{
		auto currentScene = (Scene*)Director::getInstance()->getRunningScene();
		currentScene->removeAllChildren();
	}
}
