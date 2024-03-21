import java.security.spec.EllipticCurve;

public class DPCompositeDemo {

    public static void main(String[] args) {
        
        Employee dev1 = new Developer(100, "Marco", "Code Writer");
        Employee dev2 = new Developer(101, "Mirco", "Code Planner");
        CompanyDirectory devDir = new CompanyDirectory();
        devDir.addEmployee(dev1);
        devDir.addEmployee(dev2);

        Employee man1 = new Manager(001, "Gianluca", "CEO");
        Employee man2 = new Manager(010, "Mario", "Manager Risorse Umane");
        CompanyDirectory manDir = new CompanyDirectory();
        manDir.addEmployee(man1);
        manDir.addEmployee(man2);

        CompanyDirectory dir = new CompanyDirectory();
        dir.addEmployee(devDir);
        dir.addEmployee(manDir);

        dir.showEmployeeDetails();

    }
    
}
