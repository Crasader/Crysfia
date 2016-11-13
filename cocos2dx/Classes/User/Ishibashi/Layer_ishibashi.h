# ifndef __Layer_ishibashi__
# define __Layer_ishibashi__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
	class Layer_ishibashi : public LayerBase
	{
	protected:
		void showButton();//�{�^����\������

		void eatText();//�H�ސ���
		void erase_eatText();

		void eatTexture(int food_num);//�H�ޕ`��p �������ŕ`�悷����̂�ύX
		//void erase_eatTexture(int erase_num);

		void eatMenu();//�H�ޑI��p�E�B���h�E
		void selectedItemEvent(Ref *pSender, cocos2d::ui::ListView::EventType type);

	public:
		bool exist;
		cocos2d::Sprite * food;
		
		std::vector<std::string> food_name
		{
			"food_1",
			"food_2",
			"food_3",
			"food_4",
			"food_5",
			"food_6",
			"food_7",
			"food_8",
			"food_9",
			"food_10",
			"food_11",
			"food_12",
			"food_13",
			"food_14",
			"food_15",
		};

		std::vector<std::string> food_texture
		{
			"schwb_mu.png",
			"chihyaa.png",
			"harukasan.png",
			"schwb_mu.png",
			"chihyaa.png",
			"harukasan.png",
			"schwb_mu.png",
			"chihyaa.png",
			"harukasan.png",
			"schwb_mu.png",
			"chihyaa.png",
			"harukasan.png",
			"schwb_mu.png",
			"chihyaa.png",
			"harukasan.png",
		};

		CREATE_FUNC(Layer_ishibashi);
		Layer_ishibashi();
		~Layer_ishibashi();
		bool init() override;
		void setup() override;
		void update(float delta) override;
	};
}

# endif // __Layer_ishibashi__