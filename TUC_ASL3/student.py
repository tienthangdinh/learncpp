class Course:
    def __init__(self, name : str, cp : int):
        self.name = name
        self.cp = cp
        self.docent = None
    def getName(self):
        return self.name
    def getCP(self):
        return self.cp
    def getDocent(self):
        return self.docent
    def removeDocent(self):
        self.docent = None
    def setDocent(self, docent : Docent):
        if self.name in docent.getCourses():
            self.docent = docent
            return True
        return False
    def __eq__(self, other):
        return self.name == other.name
    
class Docent:
    def __init__(self, firstName : str, surName : str, email : str):
        self.firstName = firstName
        self.surName = surName
        self.email = email
        self.courses = []
        self.alreadycourses = []

    def getFirstName(self):
        return self.firstName
    def getSurName(self):
        return self.surName
    def getEmail(self):
        return self.email
    
    def addCourse(self, courseName : str):
        if courseName not in self.courses:
            self.courses.append(courseName)

    def getCourses(self):
        return self.courses
    
    def getAlreadyCourses(self):
        return self.alreadycourses

    def __eq__(self, other):
        return self.firstName == other.firstName and self.surName == other.surName



class Versuch:
    def __init__(self, course : Course, grade : str):
        self.course = course
        self.grade = grade
        self.failedattempts = 1 if grade == "5.0" else 0

    def addVersuch(self, grade : str):
        self.grade = grade
        if self.grade == "5.0":
            self.failedattempts+=1

    def __eq__(self, other):
        return self.course == other.course

class Student:
    def __init__(self, firstName: str, surName : str, email : str, studentID : int):
        self.firstName = firstName
        self.surName = surName
        self.email = email
        self.studentID = studentID
        self.courselist = []


    def addCourse(self, course : Course, grade : str):
        newVersuch = Versuch(course, grade)
        if newVersuch in self.courselist:
            index = self.courselist.index(newVersuch)
            self.courselist[index].addVersuch(grade)
        else:
            self.courselist.append(newVersuch)

    def getFirstName(self):
        return self.firstName
    def getSurName(self):
        return self.surName
    def getEmail(self):
        return self.email
    def getStudentID(self):
        return self.studentID
    
    def getCourses(self):
        return [versuch.course for versuch in self.courselist]
    
    def getGradeInCourse(self, course : Course):
        for versuch in self.courselist:
            if versuch.course == course:
                return versuch.grade     
        return None
    
    def getNumberOfFailedAttempts(self, course : Course):
        for versuch in self.courselist:
            if versuch.course == course:
                return versuch.failedattempts
        return None
    
    def getReachedCP(self):
        return sum([versuch.course.cp for versuch in self.courselist if versuch.grade != "5.0"])
    
    def getAverageGrade(self):
        passed_versuche = [versuch for versuch in self.courselist if versuch.grade != "5.0"]
        fullcp = self.getReachedCP()
        avg_grade = 0.0
        for versuch in passed_versuche:
                avg_grade += float(versuch.grade) * versuch.course.cp / fullcp
        return avg_grade



class University:
    def __init__(self, name : str):
        self.name = name
        self.docents = []
        self.courses = []
        self.students = []
        self.matrikelnr = 0

    def addDocent(self, docent : Docent):
        if docent not in self.docents:
            self.docents.append(docent)
            return True
        return False
    
    def getDocent(self, firstName : str, surName : str):
        for docent in self.docents:
            if docent.getSurName() == surName and docent.getFirstName() == firstName:
                return docent
        return None
    
    def getListOfDocents(self):
        return self.docents
    
    def addCourse(self, courseName : str, cp : int):
        newcourse = Course(name=courseName, cp=cp)
        self.courses.append(newcourse)
        return newcourse
    
    def getCourse(self, courseName: str):
        for course in self.courses:
            if course.getName() == courseName:
                return course
        return None
    
    def getListOfCourses(self):
        return self.courses
    def getListOfEmptyCourses(self):
        emptycourses = []
        # for course in self.courses:
        #     if course.docent == None:
        #         emptycourses.append(course)
        # return emptycourses
        return [course for course in self.courses if course.getDocent() is None]
    
    def addStudent(self, firstname : str, surname : str, email : str):
        self.matrikelnr+=1
        newstudent = Student(firstName=firstname, surName=surname, email=email, studentID=f"{self.matrikelnr:06d}")
        self.students.append(newstudent)

    def removeStudent(self, student : Student):
        if student in self.students:
            self.students.remove(student)
            return True
        return False
    
    def getStudent(self, firstName : str, surName : str):
        for student in self.students:
            if student.firstName == firstName and student.surName == surName:
                return student
        return None
    
    def getListofStudents(self):
        return self.students
    
    def distributeCourse(self):
        emptycourses = self.getListofEmptyCourses()
        for emptycourse in emptycourses:
            potential_docents = []
            for docent in self.getListOfDocents():
                if emptycourse in docent.getCourses():
                    potential_docents.append((docent, len(docent.getAlreadyCourses())))
            potential_docents = sorted(potential_docents, key=lambda x : x[1])
            chosen_docent = potential_docents[0][0]
            chosen_docent.addCourse(emptycourse.getName())
            emptycourse.docent = chosen_docent
        
    def getStudentByGrade(self, courses : list):
        filtered_students = []
        for student in self.students:
            student_courses = student.getCourses()
            if any (c in student_courses for c in courses):
                filtered_students.append(student)
        return sorted(filtered_students, key=lambda stud : stud.getAverageGrade())

    def getAverageGradeOfCourse(self, course : Course):
        notes = []
        for student in self.students:
            if course in student.getCourses():
                note = student.getGradeInCourses(course)
                if note and note != "5.0":
                    notes.append(float(note))
        return sum(notes) / len(notes)
        
    def getCoursesByFailureRate(self):
        failure_rates = []
        for course in self.courses:
            all_students = 0
            failed_students = 0
            for student in self.students:
                if course in student.getCourses():
                    all_students+=1
                    if student.getGradeInCourses(course) == "5.0":
                        failed_students+=1
            rate = failed_students / all_students if all_students > 0 else 0
            failure_rates.append((course, rate))
        failure_rates = sorted(failure_rates, key=lambda el : el[1], reverse = True)
        return failure_rates
    
class UniversityNetwork:
    def __init__(self):
        self.universities = []
    def registerUniversity(self, university : University):
        if university in self.universities:
            return False
        self.universities.append(university)
        return True
    
    def getUniversityByStudentCount(self):
        sorteduniversities = sorted(self.universities, key=lambda x: len(x.getListofStudents()), reverse=True)
        return sorteduniversities
    
    def getUniversityByCoveredCourses(self):
        def count_covered(uni):
            return sum(1 for c in uni.getListOfCourses() if c.getDocent() is not None)
        return sorted(self.universities, key=count_covered, reverse=True)

                


