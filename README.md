# Manage Car Repair Shop - 1ºY 2ºS

The aim is to develop an application to help a workshop employee manage their bookings. The application should keep information on customers and the times available for bookings, as well as bookings on hold. The application should allow the following operations to be carried out interactively:

- Book wash or maintenance - a customer makes a booking to have their car washed or serviced.
 - Pre-book a wash or service - a customer wants to book a wash or service, but has no available time and signs up to a waiting list to be given priority if a booking is canceled. 
- Cancel a reservation - delete a reservation. If there is a pre-booking compatible with the unoccupied time and day, it will be placed immediately.
- Cancel a pre-booking - delete a pre-booking request. 
- List washing and maintenance bookings and pre-bookings sorted by date (oldest first). -
 List a customer's bookings and pre-bookings sorted by date (most recent first).

The working hours are from 8 a.m. to 6 p.m., with no lunch break. It takes half an hour to wash a car and an hour to carry out maintenance. When an operation finishes, it is deleted from the respective booking list.

To solve this problem, you must define and use appropriate data structures. These structures should be defined in a separate source file. Solutions that are efficient from the point of view of the memory space occupied are valued, namely sorting solutions that use auxiliary data structures with pointers to the actual records rather than structures with the records themselves.

All relevant information should be stored in text files. The application should have an option to load the information and another to save the current status of the reservations. The program should also be properly secured.
