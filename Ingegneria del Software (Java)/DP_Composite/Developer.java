public class Developer implements Employee {    //Leaf

    private String name;
    private long empID;
    private String role;

    public Developer(long empID, String name, String role) {

        this.empID = empID;
        this.name = name;
        this.role = role;

    }

    @Override
    public void showEmployeeDetails() {
        
        System.out.println(empID + "\t:\t" + name + "\t[ " + role + " ]");
        
    }

}
