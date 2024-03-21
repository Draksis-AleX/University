public class Demo {
    public static void main(String[] args) {
        
        Student model = retrieveStudentFromDatabase();
        StudentView view = new StudentView();
        
        StudentController studentController = new StudentController(model, view);

        studentController.updateView();

        studentController.setStudentName("John");

        studentController.updateView();
    }

    public static Student retrieveStudentFromDatabase() {
        Student student = new Student();
        student.setName("Robert");
        student.setRollNum("10");
        return student;
    } 
}
