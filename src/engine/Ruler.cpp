#include "Ruler.hpp"

void Ruler::execute(Commande com, Etat state)
{
	if (com.getType() == "Move")
	{
		int i = 0;
		ElementList liste = state.getList();
		for (i = 0; i < state.getSize(); i++)
		{
			if (liste[i]->getX() == commandeX && liste[i]->getY() == commandeY && liste[i]->getUid() != 0)
				return;
		}
		int x = commandeX - liste[liste.findUid(CommandeUID)]->getX;
		int y = commandeY - liste[liste.findUid(CommandeUID)]->getY;
		if (x < 0) x = -x;
		if (y < 0) y = -y;
		if (x + y > liste[liste.findUid(CommandeUID)]->getAttribute("deplacement")) return;
		
		//create action here
		//ActionFactory.create("Move",CommandeUID,CommandeX,CommandeY);
	}
}