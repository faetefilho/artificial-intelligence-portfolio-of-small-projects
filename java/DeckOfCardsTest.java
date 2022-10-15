package chapter_07;

public class DeckOfCardsTest 
{
    public static void main(String[] args)
    {
        DeckOfCards myDeckOfCards = new DeckOfCards();
        myDeckOfCards.shuffle();  // shuffle cards

        // print all 52 cards in the order they are dealt
        for (int i = 1; i <= 52; i++)
        {   // when a card is output as a string, the card's toString
            // method is implicitly invoked 
            System.out.printf("%-19s", myDeckOfCards.dealCard());

            if (i % 4 == 0)
            {
                System.out.println();
            }
        }
    }
}
