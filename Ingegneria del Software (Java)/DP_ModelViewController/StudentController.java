public class StudentController {    //controller class
    private Student model;
    private StudentView view;

    public StudentController(Student model, StudentView view) {
        this.model = model;
        this.view = view;
    }

    public void setStudentName(String name) { model.setName(name); }
    public void setStudentRollNum(String rollNum) {model.setRollNum(rollNum); }

    public String getStudentName() { return model.getName(); }
    public String getStudentRollNumm() { return model.getRollNum(); }

    public void updateView() {
        view.printStudentDetails(getStudentName(), getStudentRollNumm());
    }
}
