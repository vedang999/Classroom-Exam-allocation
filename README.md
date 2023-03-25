# Classroom-Exam-allocation
Question
You need to develop a system for registration, allotment of classrooms for lectures as well as 
examination allotment for students. Maintain one list for students data. Every student has 
registered for five courses. Maintain information such as name of student, enrolment number, 
courses taken etc. Every course will also have its list of students taking that course, slot 
assigned to that course, maintained separately. Multiple courses (across semesters and also 
for the same semeter) can be assigned to the same slot.
Maintain another list of classrooms. For every room, maintain the number of seats in that 
room. Also assume that there are 4 rows in each room and each bench can provide seats for 3 
students. The number of benches per row would depend on the class capacity.
Implement features/functions such as : 
1. Adding a student to the student-list. When adding a student to the student-list, verify 
that a student cannot take 2 courses in the same slot.
2. Deletion of a student from the student-list. When deleting a student, ensure that the 
student record is also deleted from the courses taken by that student.
3. Adding a course to the course list. When deleting a course, ensure that no student has 
taken that course.
4. Allotment of classrooms for lectures. Allot every course to a classroom such that the 
capacity of the room is larger than the number of students registered for the course. 
Allot the classrooms in the most optimal way such that minimum number of 
classrooms are utilised. Two courses in the same slot to get different rooms. Also as 
much as possible the same room is to be used for consecutive slots for students of the 
same class/semester. If it is not possible, then different rooms can be utilised. Detect 
the situation if a room cannot be allocated to some course in a particular slot. In such 
case make sure that least number of courses are not allocated the rooms and these 
courses together have as less number of students as possible. 
5. Allotment of classrooms for exams. Seats in the classroom can be numbered based on 
row-number, bench-number etc. When assigning seats in the examination hall, ensure 
that no students of the same course can be assigned adjacent seats.
6. Print the list of students and the exam seat allotted to each student for a given slot.
