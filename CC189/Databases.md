### 14.0
* Denormalized vs Normalized
   * Normalized databases are designed to minimize redundancy
   * Denormalized databases are designed to optimize read time(not require expensive joins)

```
SELECT StudentName
FROM Students
INNER JOIN
  (SELECT StudentID FROM StudentCourse GROUP BY CourseID HAVING count(*) > 1) T
ON T.StudentID = Students.StudentID
```
