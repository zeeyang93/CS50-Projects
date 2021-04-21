-- Keep a log of any SQL queries you execute as you solve the mystery.

-- List all crimes from that day and location
SELECT * FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28 AND street = 'Chamberlin Street';

-- Description:
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

SELECT id,name,transcript FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE '%courthouse%';

-- 161 | Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162 | Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- 163 | Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT id,activity,hour,minute,license_plate FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30;

-- id | activity | hour | minute | license_plate
-- 260 | exit | 10 | 16 | 5P2BI95
-- 261 | exit | 10 | 18 | 94KL13X
-- 262 | exit | 10 | 18 | 6P58WS2
-- 263 | exit | 10 | 19 | 4328GD8
-- 264 | exit | 10 | 20 | G412CB7
-- 265 | exit | 10 | 21 | L93JTIZ
-- 266 | exit | 10 | 23 | 322W7JE
-- 267 | exit | 10 | 23 | 0NTHK55

SELECT id,account_number,atm_location,transaction_type,amount FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw';

-- id | account_number | year | month | day | atm_location | transaction_type | amount
-- 246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
-- 264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
-- 266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
-- 267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
-- 269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
-- 288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
-- 313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
-- 336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35

SELECT * FROM flights
WHERE year = 2020 AND month = 7 AND day = 29
ORDER BY hour;

-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
-- 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20

SELECT * FROM airports
WHERE id = 4;

-- Origin
-- id | abbreviation | full_name | city
-- 8 | CSF | Fiftyville Regional Airport | Fiftyville

-- Destination
-- id | abbreviation | full_name | city
-- 4 | LHR | Heathrow Airport | London

SELECT * FROM passengers
WHERE flight_id = 36;

-- flight_id | passport_number | seat
-- 36 | 7214083635 | 2A
-- 36 | 1695452385 | 3B
-- 36 | 5773159633 | 4A
-- 36 | 1540955065 | 5C
-- 36 | 8294398571 | 6C
-- 36 | 1988161715 | 6D
-- 36 | 9878712108 | 7A
-- 36 | 8496433585 | 7B

SELECT * FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

-- id | caller | receiver | year | month | day | duration
-- 221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
-- 224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
-- 233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
-- 251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
-- 254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
-- 255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
-- 261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
-- 279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
-- 281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54



-- Queries to find THIEF: Ernest
SELECT name FROM people WHERE phone_number
IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60)
INTERSECT
SELECT name FROM people WHERE license_plate
IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30)
INTERSECT
SELECT name FROM people WHERE passport_number
IN (SELECT passport_number FROM passengers WHERE flight_id = 36)
INTERSECT
SELECT name FROM people WHERE id
IN (SELECT person_id FROM bank_accounts WHERE account_number
IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw'));

-- Queries to find ACCOMPLICE: Ernest
SELECT name FROM people WHERE phone_number
IN (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller
IN (SELECT phone_number FROM people WHERE name = 'Ernest'));