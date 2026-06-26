#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

////// test

#define MAX_USERS 100
#define MAX_VEHICLES 100
#define MAX_TRIPS 100
#define MAX_BOOKINGS 100
#define CO2_SAVED_PER_KM 0.12  // 0.12 kg of CO2 saved per km per passenger
#define FUEL_SAVED_PER_KM 0.05 // 0.05 Liters saved per km per passenger

// Hardcoded route node system for automated index matching
const char *ROUTE_STATIONS[] = {"TK", "BK", "TSK", "RSK", "CCV", "PL", "CADT"};
#define ROUTE_STATIONS_COUNT 7

typedef enum
{
    DRIVER,
    PASSENGER
} UserRole;

typedef enum
{
    MOTORBIKE,
    CAR
} VehicleType;

typedef struct
{
    int id;
    char name[50];
    char phone[20];
    UserRole role;
} User;

typedef struct
{
    int id;
    int ownerId;
    VehicleType type;
    char plateNumber[20];
    int capacity;
} Vehicle;

typedef struct
{
    int id;
    int driverId;
    int vehicleId;
    char departure[50];
    char destination[50];
    char date[20];
    int availableSeats;
    float distanceKm;
} Trip;

typedef struct
{
    int id;
    int passengerId;
    int tripId;
    int seatsBooked;
} Booking;

// Global Application Arrays
User users[MAX_USERS];
int userCount = 0;

Vehicle vehicles[MAX_VEHICLES];
int vehicleCount = 0;

Trip trips[MAX_TRIPS];
int tripCount = 0;

Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;

// Function Prototypes
void registerUser();
void registerVehicle();
void createTrip();
void searchTrips();
void bookTrip();
void showEnvironmentalImpact();
void viewAllData();
void clearInputBuffer();
void saveData();
void loadData();

// Helper Routing Internals
int getStationIndex(const char *stationName)
{
    for (int i = 0; i < ROUTE_STATIONS_COUNT; i++)
    {
        if (strcasecmp(ROUTE_STATIONS[i], stationName) == 0)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    loadData();
    int choice;
    while (1)
    {
        printf("\n==================================================\n");
        printf("    SMART MOTORBIKE & CAR RIDE SHARING SYSTEM     \n");
        printf("==================================================\n");
        printf("1. Register User (Driver / Passenger)\n");
        printf("2. Register Vehicle (Drivers Only)\n");
        printf("3. Create Trip Route (Drivers Only)\n");
        printf("4. Search Trips (Smart Route Matching)\n");
        printf("5. Book Trip & Update Seats\n");
        printf("6. View Environmental Impact & Reports\n");
        printf("7. View Management Records Data\n");
        printf("8. Save & Exit Application\n");
        printf("--------------------------------------------------\n");
        printf("Enter your choice (1-8): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a valid number configuration.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            registerVehicle();
            break;
        case 3:
            createTrip();
            break;
        case 4:
            searchTrips();
            break;
        case 5:
            bookTrip();
            break;
        case 6:
            showEnvironmentalImpact();
            break;
        case 7:
            viewAllData();
            break;
        case 8:
            saveData();
            printf("\nSystems successfully written to memory storage. Goodbye!\n");
            return 0;
        default:

            printf("Try again.\n");
        }
    }
    return 0;
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void registerUser()
{
    system("cls||clear");
    if (userCount >= MAX_USERS)
    {
        printf("System Error: Maximum capacity for structural user arrays reached.\n");
        return;
    }
    User newUser;
    newUser.id = userCount + 101; // Assign safe offset User ID value

    printf("\n--- Register User Account Structure ---\n");
    printf("Enter Full Name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = 0;

    printf("Enter Active Phone Number: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")] = 0;

    int roleChoice;
    printf("Select System Access Account Type Role (0: DRIVER, 1: PASSENGER): ");
    scanf("%d", &roleChoice);
    clearInputBuffer();

    if (roleChoice == 0)
    {
        newUser.role = DRIVER;
    }
    else if (roleChoice == 1)
    {
        newUser.role = PASSENGER;
    }
    else
    {
        printf("Out of bounds entry parameter choice. Defaulting account role to PASSENGER.\n");
        newUser.role = PASSENGER;
    }

    users[userCount] = newUser;
    userCount++;
    printf("Success: User '%s' added safely with ID: %d\n", newUser.name, newUser.id);
}

void registerVehicle()
{
    if (vehicleCount >= MAX_VEHICLES)
    {
        printf("System Error: Vehicle storage space is completely full.\n");
        return;
    }

    int inputOwnerId;
    printf("\n--- Register Vehicle Data Assets ---\n");
    printf("Verify System Driver Owner ID number: ");
    scanf("%d", &inputOwnerId);
    clearInputBuffer();

    int foundDriverIdx = -1;
    for (int i = 0; i < userCount; i++)
    {
        if (users[i].id == inputOwnerId)
        {
            if (users[i].role == DRIVER)
            {
                foundDriverIdx = i;
                break;
            }
            else
            {
                printf("Error: This target user profile is listed as a PASSENGER profile.\n");
                return;
            }
        }
    }

    if (foundDriverIdx == -1)
    {
        printf("Invalid Error: Target driver configuration identification index not detected.\n");
        return;
    }

    Vehicle newVehicle;
    newVehicle.id = vehicleCount + 501; // Assigned vehicle asset code offset block
    newVehicle.ownerId = inputOwnerId;

    int typeChoice;
    printf("Select Vehicle Classification (0: MOTORBIKE, 1: CAR): ");
    scanf("%d", &typeChoice);
    clearInputBuffer();
    newVehicle.type = (typeChoice == 0) ? MOTORBIKE : CAR;

    printf("Enter License Plate Number: ");
    fgets(newVehicle.plateNumber, sizeof(newVehicle.plateNumber), stdin);
    newVehicle.plateNumber[strcspn(newVehicle.plateNumber, "\n")] = 0;

    if (newVehicle.type == MOTORBIKE)
    {
        printf("Default max payload capacity set for Motorbike profile (1 seat open).\n");
        newVehicle.capacity = 1;
    }
    else
    {
        printf("Enter Max Passenger Seating Capacity configuration (1-7 seats): ");
        scanf("%d", &newVehicle.capacity);
        clearInputBuffer();
        if (newVehicle.capacity <= 0 || newVehicle.capacity > 7)
        {
            newVehicle.capacity = 4; // Normalized standard fallback
        }
    }

    vehicles[vehicleCount] = newVehicle;
    vehicleCount++;
    printf("Success: Vehicle asset saved! Resource Unit ID: %d linked to Driver ID: %d\n", newVehicle.id, newVehicle.ownerId);
}

void createTrip()
{
    if (tripCount >= MAX_TRIPS)
    {
        printf("Target capacity limits breached for trip creation processing.\n");
        return;
    }

    int inputDriverId;
    printf("\n--- Driver Trip Initialization Module ---\n");
    printf("Enter Your Driver ID Number verification: ");
    scanf("%d", &inputDriverId);
    clearInputBuffer();

    int driverVehicleIdx = -1;
    for (int i = 0; i < vehicleCount; i++)
    {
        if (vehicles[i].ownerId == inputDriverId)
        {
            driverVehicleIdx = i;
            break;
        }
    }

    if (driverVehicleIdx == -1)
    {
        printf("Authentication Failure: No registered tracking asset found for Driver ID %d.\n", inputDriverId);
        return;
    }

    Trip newTrip;
    printf("\nAvailable Station Codes: [TK, BK, TSK, RSK, CCV, PL]\n");
    printf("Enter Departure Station code abbreviation: ");
    fgets(newTrip.departure, sizeof(newTrip.departure), stdin);
    newTrip.departure[strcspn(newTrip.departure, "\n")] = 0;

    // AUTOMATICALLY SET DESTINATION TO CADT
    strcpy(newTrip.destination, "CADT");
    printf("Destination automatically set to: CADT\n");

    int depIdx = getStationIndex(newTrip.departure);
    int destIdx = getStationIndex(newTrip.destination);

    if (depIdx == -1 || destIdx == -1)
    {
        printf("Validation Error: Undefined route profile strings inputted.\n");
        return;
    }
    if (depIdx >= destIdx)
    {
        printf("Routing Error: Departure node index must exist earlier than destination route flow (Cannot depart from CADT to CADT).\n");
        return;
    }

    printf("Enter Date parameter value format (e.g. DD/MM/YYYY): ");
    fgets(newTrip.date, sizeof(newTrip.date), stdin);
    newTrip.date[strcspn(newTrip.date, "\n")] = 0;

    printf("Enter estimated distance values for this route vector block (in Km): ");
    scanf("%f", &newTrip.distanceKm);
    clearInputBuffer();

    newTrip.id = tripCount + 901;
    newTrip.driverId = inputDriverId;
    newTrip.vehicleId = vehicles[driverVehicleIdx].id;
    newTrip.availableSeats = vehicles[driverVehicleIdx].capacity;

    trips[tripCount] = newTrip;
    tripCount++;
    printf("Trip initialized successfully! Allocation Tracker ID: %d [Seats Open: %d]\n", newTrip.id, newTrip.availableSeats);
}

void searchTrips()
{
    char sDep[50], sDest[50];
    printf("\n--- Smart Passenger Search Engine Query ---\n");
    printf("Enter Your Requested Departure Station Node: ");
    fgets(sDep, sizeof(sDep), stdin);
    sDep[strcspn(sDep, "\n")] = 0;

    // AUTOMATICALLY SET DESTINATION TO CADT
    strcpy(sDest, "CADT");
    printf("Target Terminal Destination automatically set to: CADT\n");

    int pDepIdx = getStationIndex(sDep);
    int pDestIdx = getStationIndex(sDest);

    if (pDepIdx == -1 || pDestIdx == -1)
    {
        printf("Network Error: One or more entry node definitions are out-of-bounds.\n");
        return;
    }
    if (pDepIdx >= pDestIdx)
    {
        printf("Flow Error: Desired location matches require correct forward coordinate index progression.\n");
        return;
    }

    printf("\n--- Available Smart-Matched Ride Opportunities ---\n");
    printf("%-10s %-15s %-12s %-12s %-12s %-10s\n", "Trip ID", "Driver ID", "From", "To", "Date", "Seats Open");
    printf("------------------------------------------------------------------------\n");

    int matches = 0;
    for (int i = 0; i < tripCount; i++)
    {
        int dDepIdx = getStationIndex(trips[i].departure);
        int dDestIdx = getStationIndex(trips[i].destination);

        // Smart Logic matching: Driver encompasses Passenger pick/drop coordinates
        if (dDepIdx <= pDepIdx && pDestIdx <= dDestIdx && trips[i].availableSeats > 0)
        {
            printf("%-10d %-15d %-12s %-12s %-12s %-10d\n",
                   trips[i].id, trips[i].driverId, trips[i].departure,
                   trips[i].destination, trips[i].date, trips[i].availableSeats);
            matches++;
        }
    }
    if (matches == 0)
    {
        printf("No existing dynamic vectors running via this routing match sector currently.\n");
    }
}

void bookTrip()
{
    if (bookingCount >= MAX_BOOKINGS)
    {
        printf("Capacity Limit Error: Array systems are maxed out.\n");
        return;
    }

    int inputPassId, inputTripId, reqSeats;
    printf("\n--- Passenger Booking Engine Terminal Interface ---\n");
    printf("Enter Passenger structural User ID code: ");
    scanf("%d", &inputPassId);

    int passengerValid = 0;
    for (int i = 0; i < userCount; i++)
    {
        if (users[i].id == inputPassId && users[i].role == PASSENGER)
        {
            passengerValid = 1;
            break;
        }
    }
    if (!passengerValid)
    {
        printf("Validation Error: Valid passenger verification code missing.\n");
        clearInputBuffer();
        return;
    }

    printf("Enter target allocated Trip ID code: ");
    scanf("%d", &inputTripId);

    int tripIdx = -1;
    for (int i = 0; i < tripCount; i++)
    {
        if (trips[i].id == inputTripId)
        {
            tripIdx = i;
            break;
        }
    }

    if (tripIdx == -1)
    {
        printf("Database matching system Error: Trip reference entry missing.\n");
        clearInputBuffer();
        return;
    }

    printf("Quantity of processing seats requested: ");
    scanf("%d", &reqSeats);
    clearInputBuffer();

    if (reqSeats <= 0)
    {
        printf("Logical Error: Input values must exceed baseline zero constraints.\n");
        return;
    }

    if (trips[tripIdx].availableSeats >= reqSeats)
    {
        // Safe modification mapping updates executed concurrently
        trips[tripIdx].availableSeats -= reqSeats;

        Booking newBooking;
        newBooking.id = bookingCount + 2001;
        newBooking.passengerId = inputPassId;
        newBooking.tripId = inputTripId;
        newBooking.seatsBooked = reqSeats;

        bookings[bookingCount] = newBooking;
        bookingCount++;

        printf("Success! Booking Reference ID Token assigned: %d\n", newBooking.id);
        printf("Updated remaining seats tracking status for Trip ID %d is now: %d\n", trips[tripIdx].id, trips[tripIdx].availableSeats);
    }
    else
    {
        printf("Booking processing failed: Insufficient seats available. Currently open: %d\n", trips[tripIdx].availableSeats);
    }
}

void showEnvironmentalImpact()
{
    float totalKmTraveledByPassengers = 0;

    for (int i = 0; i < bookingCount; i++)
    {
        int targetTripId = bookings[i].tripId;
        for (int j = 0; j < tripCount; j++)
        {
            if (trips[j].id == targetTripId)
            {
                totalKmTraveledByPassengers += (trips[j].distanceKm * bookings[i].seatsBooked);
                break;
            }
        }
    }

    float calculatedCarbonSavings = totalKmTraveledByPassengers * CO2_SAVED_PER_KM;
    float calculatedFuelSavings = totalKmTraveledByPassengers * FUEL_SAVED_PER_KM;

    printf("\n==================================================\n");
    printf("    ECO-METRICS & SYSTEM PERFORMANCE REPORT       \n");
    printf("==================================================\n");
    printf(" Total System Active Accounts  : %d User instances\n", userCount);
    printf(" Total Registered Fleet Vehicles: %d Vehicle nodes\n", vehicleCount);
    printf(" Total Initialized Trip Offers  : %d Tracked lines\n", tripCount);
    printf(" Total Confirmed Passenger Rides: %d Complete Bookings\n", bookingCount);
    printf("--------------------------------------------------\n");
    printf(" Accumulative Shared Ride Distance: %.2f Passenger-Km\n", totalKmTraveledByPassengers);
    printf(" Total Estimated Fuel Saved       : %.2f Liters \n", calculatedFuelSavings);
    printf(" Carbon Footprint CO2 Reduction  : %.2f Kg Saved\n", calculatedCarbonSavings);
    printf("==================================================\n");
}

void viewAllData()
{
    printf("\n=== REGISTRATION USERS REPORT DATABASE ===\n");
    for (int i = 0; i < userCount; i++)
    {
        printf("User Index ID: %d | Name: %s | Contact Phone: %s | Role Status: %s\n",
               users[i].id, users[i].name, users[i].phone,
               (users[i].role == DRIVER) ? "DRIVER" : "PASSENGER");
    }
    printf("\n=== VEHICLE DATA INVENTORY BLOCK ===\n");
    for (int i = 0; i < vehicleCount; i++)
    {
        printf("Vehicle asset ID: %d | Owner Driver ref ID: %d | Code Plate: %s | Base Limit Capacity: %d\n",
               vehicles[i].id, vehicles[i].ownerId, vehicles[i].plateNumber, vehicles[i].capacity);
    }
}

void saveData()
{
    FILE *fUsers = fopen("users.dat", "wb");
    if (fUsers)
    {
        fwrite(&userCount, sizeof(int), 1, fUsers);
        fwrite(users, sizeof(User), userCount, fUsers);
        fclose(fUsers);
    }

    FILE *fVehicles = fopen("vehicles.dat", "wb");
    if (fVehicles)
    {
        fwrite(&vehicleCount, sizeof(int), 1, fVehicles);
        fwrite(vehicles, sizeof(Vehicle), vehicleCount, fVehicles);
        fclose(fVehicles);
    }

    FILE *fTrips = fopen("trips.dat", "wb");
    if (fTrips)
    {
        fwrite(&tripCount, sizeof(int), 1, fTrips);
        fwrite(trips, sizeof(Trip), tripCount, fTrips);
        fclose(fTrips);
    }

    FILE *fBookings = fopen("bookings.dat", "wb");
    if (fBookings)
    {
        fwrite(&bookingCount, sizeof(int), 1, fBookings);
        fwrite(bookings, sizeof(Booking), bookingCount, fBookings);
        fclose(fBookings);
    }
    printf("\nSystems safely serialized out to binaries.\n");
}

void loadData()
{
    FILE *fUsers = fopen("users.dat", "rb");
    if (fUsers)
    {
        if (fread(&userCount, sizeof(int), 1, fUsers) == 1)
        {
            fread(users, sizeof(User), userCount, fUsers);
        }
        fclose(fUsers);
    }

    FILE *fVehicles = fopen("vehicles.dat", "rb");
    if (fVehicles)
    {
        if (fread(&vehicleCount, sizeof(int), 1, fVehicles) == 1)
        {
            fread(vehicles, sizeof(Vehicle), vehicleCount, fVehicles);
        }
        fclose(fVehicles);
    }

    FILE *fTrips = fopen("trips.dat", "rb");
    if (fTrips)
    {
        if (fread(&tripCount, sizeof(int), 1, fTrips) == 1)
        {
            fread(trips, sizeof(Trip), tripCount, fTrips);
        }
        fclose(fTrips);
    }

    FILE *fBookings = fopen("bookings.dat", "rb");
    if (fBookings)
    {
        if (fread(&bookingCount, sizeof(int), 1, fBookings) == 1)
        {
            fread(bookings, sizeof(Booking), bookingCount, fBookings);
        }
        fclose(fBookings);
    }
}