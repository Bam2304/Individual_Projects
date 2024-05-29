
import java.util.*;


public class TicTacToe {

static HashSet<Integer> u_set = new HashSet<Integer>();
static HashSet<Integer> c_set = new HashSet<Integer>();

public static void main(String[] args){
    char[][] board = {{'_',' ','_',' ','_'}, 
                      {'_',' ','_',' ','_'},
                      {'_',' ','_',' ','_'}};
    

print_board(board);


Scanner scnr = new Scanner(System.in);
Random rand = new Random();
int cpu_position;
char w;

while(true){ //Repeat until board is full

    System.out.print("Choose a position 1 - 9: "); //Getting the user's position
    int user_position = scnr.nextInt();
    while((u_set.contains(user_position) || c_set.contains(user_position) || user_position > 9 || user_position < 1)){
        System.out.println("Cannot choose that position. Choose another: ");
        user_position = scnr.nextInt();
    }
    updateboard("You", board, user_position);
    
    w = checkWinner(); //check if the user won
    //System.out.println(w);
    if (w == 'X'){
        System.out.println("You Won! Congratulations!");
        break;
    }

    System.out.println();

    cpu_position = rand.nextInt(1, 10); //Generating the computer's position randomly
    while((c_set.contains(cpu_position) || u_set.contains(cpu_position))){
        cpu_position = rand.nextInt(1, 10);
    }


    System.out.println("Computer's Choice: " + cpu_position);
    updateboard("CPU", board, cpu_position);

    System.out.println();

    w = checkWinner(); //check if the cpu won
    //System.out.println(w);
    if (w == 'O'){
        System.out.println("Better luck next time; the computer won...");
        break;
    }
    else if ((u_set.size() + c_set.size() == 9)){ //in the case of a draw
        System.out.println("It's a draw...");
        break;
    }
}

//System.out.print("Play Again? (y/n) ");
//String answer = scnr.nextLine();

scnr.close();

}

static void print_board(char[][] g_board){
    for(int i = 0; i < g_board.length; i++){
        for(int j = 0; j < g_board[i].length; j++){
            System.out.print(g_board[i][j]);
        }
        System.out.println();
    }   
}

static char checkWinner(){

    
    HashSet<Integer> r1 = new HashSet<Integer>();
    r1.add(1); r1.add(2); r1.add(3);
    HashSet<Integer> r2 = new HashSet<Integer>();
    r2.add(4); r2.add(5); r2.add(6);
    HashSet<Integer> r3 = new HashSet<Integer>();
    r3.add(7); r3.add(8); r3.add(9);
    HashSet<Integer> c1 = new HashSet<Integer>();
    c1.add(1); c1.add(4); c1.add(7);
    HashSet<Integer> c2 = new HashSet<Integer>();
    c2.add(2); c2.add(5); c2.add(8);
    HashSet<Integer> c3 = new HashSet<Integer>();
    c3.add(3); c3.add(6); c3.add(9);
    HashSet<Integer> d1 = new HashSet<Integer>();
    d1.add(1); d1.add(5); d1.add(9);
    HashSet<Integer> d2 = new HashSet<Integer>();
    d2.add(3); d2.add(5); d2.add(7);

    HashSet<HashSet> everyset = new HashSet<HashSet>();
    everyset.add(r1); everyset.add(r2); everyset.add(r3);
    everyset.add(c1); everyset.add(c2); everyset.add(c3);
    everyset.add(d1); everyset.add(d2); 
    //System.out.println(everyset);
    for (HashSet s:everyset){
        if(u_set.containsAll(s)){
            return 'X';
        }
        else if (c_set.containsAll(s)){
            return 'O';
        }
        
    }
    
    return 'N';
}

static void updateboard(String user, char[][] board, int position){
    char symbol = 'X';

    if (user.equals("You")){
        symbol = 'X';
        u_set.add(position);
    }
    else if(user.equals("CPU")){
        symbol = 'O';
        c_set.add(position);
    }

    switch(position){
        case 1:
        board[0][0] = symbol;
        break;

        case 2:
        board[0][2] = symbol;
        break;

        case 3:
        board[0][4] = symbol;
        break;

        case 4:
        board[1][0] = symbol;
        break;

        case 5:
        board[1][2] = symbol;
        break;

        case 6:
        board[1][4] = symbol;
        break;

        case 7:
        board[2][0] = symbol;
        break;

        case 8:
        board[2][2] = symbol;
        break;

        case 9:
        board[2][4] = symbol;
        break;

        default:
        System.out.println("Input not valid.");

        
    }
    print_board(board);
}








}