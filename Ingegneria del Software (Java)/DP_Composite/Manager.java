public class Manager implements Employee {  //Leaf

    private String name;
    private long empID;
    private String role;

    public Manager(long empID, String name, String role) {

        this.empID = empID;
        this.name = name;
        this.role = role;

    }

    @Override
    public void showEmployeeDetails() {
        
        System.out.println(empID + "\t:\t" + name + "\t[ " + role + " ]");
        
    }

}
