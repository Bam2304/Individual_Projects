public class Athlete {

    private String name;
    private String team;
    private String sport;
    private int age;
    private int height;
    


    public Athlete(String name, String team, String sport, int age, int heightInInches){
        this.name = name;
        this.team = team;
        this.sport = sport;
        this.age = age;
        this.height = heightInInches;
        
    }

    public Athlete(){
        this.name = null;
        this.team = null;
        this.sport = null;
        this.age = 0;
        this.height = 0;
        
    }

    public void setName(String name){
        this.name = name;
    } 

    public void setAge(int age){
        this.age = age;
    }

    public void setTeam(String team){
        this.team = team;
    }

    public void setSport(String sport){
        this.sport = sport;
    }

    public void setHeight(int heightInInches){
        this.height = heightInInches;
    }

    public int getAge(){
        return this.age;
    }

    public String getName(){
        return this.name;
    }

    public String getTeam(){
        return this.team;
    }

    public String getSport(){
        return this.sport;
    }

    public int getHeight(){
        return this.height;
    }

    public String toString(){
        return "Name: " + this.name + "\n" + "Age: " + this.age + "\n" + "Team: " + this.team + "\n" + "Sport: " + this.sport + "\n" + "Height: " + this.height + " inches\n";
    }

}
