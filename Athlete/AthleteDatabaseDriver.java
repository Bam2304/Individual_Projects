import java.util.ArrayList;
import java.util.Scanner;
import java.util.Collections;

public class AthleteDatabaseDriver{

    static ArrayList<Athlete> Database = new ArrayList<Athlete>();

    public static void main(String[] args){
        
        System.out.println();
        System.out.println("Welcome to the Athlete Database!");
        Scanner scnr = new Scanner(System.in);
        boolean keepGoing = true; // Keeps track of whether user wants to quit
        
        while(keepGoing){
            System.out.println("Please choose:");
            System.out.println("1. View Database");
            System.out.println("2. Add Athlete");
            System.out.println("3. Delete Athlete");
            System.out.println("4. Search for Athlete");
            System.out.println("5. Quit");
            System.out.println();

            int choice = scnr.nextInt();
            scnr.nextLine(); // Consume the newline
            System.out.println();
            
            switch(choice){ // Based on user choice, decide what to do
                case 5:
                keepGoing = false;
                break;

                case 4:
                System.out.print("Enter athlete's name: ");
                String name1 = scnr.nextLine();
                System.out.println();
                String result = searchByName(name1);
                if(result.equals("")){
                    System.out.println("Athlete not found.");
                }
                else{
                    System.out.println(result);
                }
                break;

                case 3:
                System.out.print("Enter name of athlete to delete: ");
                String toDelete = scnr.nextLine();
                deleteAthlete(toDelete);
                System.out.println();
                break;

                case 2:
                System.out.print("Enter name: ");
                String theName = scnr.nextLine();

                System.out.print("Enter age: ");
                int theAge = scnr.nextInt();
                scnr.nextLine(); // Consume the newline

                System.out.print("Enter sport: ");
                String theSport = scnr.nextLine();

                System.out.print("Enter height in Inches: ");
                int theHeight = scnr.nextInt();
                scnr.nextLine();

                System.out.print("Enter Team name: ");
                String theTeam = scnr.nextLine();

                // Creating and adding new athlete object
                Athlete newAthlete = new Athlete(theName, theTeam, theSport, theAge, theHeight);
                Database.add(newAthlete);
                System.out.println();
                break;

                case 1:
                System.out.println("Filter by 1. age, 2. height, or 3. none?");
                int choice2 = scnr.nextInt();

                switch(choice2){
                    case 1:
                    filterByAge();
                    break;

                    case 2:
                    filterByHeight();
                    break;

                    case 3:
                    printDatabase(Database);
                    break;
                }
                

            }

        }
        scnr.close();

        
    }


    public static void printDatabase(ArrayList<Athlete> db){

        if(Database.size() == 0){
            System.out.println("Nothing in database...");
            System.out.println();
        }
        else{
            System.out.println();
            System.out.println("---------------------------Athletes------------------------------");
            System.out.println("-----------------------------------------------------------------");
            System.out.printf("%-20s   %-8s   %-10s   %-4s   %-4s %n", "NAME", "TEAM", "SPORT", "AGE", "HEIGHT (in)");
            System.out.println("-----------------------------------------------------------------");
            System.out.println("-----------------------------------------------------------------");
            for(Athlete a:db){
                System.out.printf("%-20s   %-8s   %-10s   %-4s   %-4s %n", a.getName(), a.getTeam(), a.getSport(), a.getAge(), a.getHeight());
                System.out.println("-----------------------------------------------------------------");
            }
            System.out.println();
        }
    }

    public static String searchByName(String theName){
        String result = "";
        for(Athlete a:Database){
            if(a.getName().equals(theName)){
                result = a.toString();
                break;
            }
        }
        return result;
    }

    public static void filterByAge(){
        ArrayList<Athlete> ages = Database;
        Collections.sort(ages, (a, b) -> Integer.compare(b.getAge(), a.getAge()));
        printDatabase(ages);
    }

    public static void filterByHeight(){
        ArrayList<Athlete> heights = Database;
        Collections.sort(heights, (a, b) -> Integer.compare(b.getHeight(), a.getHeight()));
        printDatabase(heights);
    }

    public static void addAthlete(String name, int age, int height, String team, String sport){
        Athlete a = new Athlete(name, team, sport, age, height);
        Database.add(a);
    }
    
    public static void deleteAthlete(String name){
        for(Athlete a1: Database){
            if(a1.getName().equals(name)){
                Database.remove(a1);
                break;
            }
        }
    }

    




}
