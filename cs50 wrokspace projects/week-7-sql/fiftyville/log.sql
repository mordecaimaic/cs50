-- Keep a log of any SQL queries you execute as you solve the mystery.


-- Find the crime scene description

SELECT crime_scene_reports.description FROM crime_scene_reports
WHERE street = 'Humphrey Street'
AND year = '2021'
AND month = '7'
AND day = '28';

-- Output
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.



-- Purpose: Go the a more detailed interview

SELECT transcript FROM interviews
WHERE year = '2021'
AND month = '7'
AND day = '28'
AND transcript LIKE '%bakery%';

-- Result:
-- 1. Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--  If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- 2. I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.


-- 3. As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.


-- Purpose: To find the bakery record, beacuse the theif leaf in 10mins afting stealing the duck, arrcoring to the 1st interviews
SELECT * FROM bakery_security_logs
WHERE year = '2021' AND month = '7' and day = '28'
AND hour = '10' AND minute <= '25'
AND activity = 'exit';
-- Deduction: The theief must in this list



-- Purpose: To find the atm record, arrcoring to the 2rd interviews
SELECT * FROM atm_transactions
WHERE year = '2021'
AND month = '7'
AND day = '28'
AND transaction_type = 'transaction_type';



-- Purpose: To find the atm record, arrcoring to the 3st interviews
SELECT * FROM phone_calls
WHERE year = '2021'
AND month = '7'
AND day = '28'
AND duration < '60';



-- Purpose: To find the flight record, arrcoring to the 3st interviews
SELECT * FROM flights
JOIN passengers ON flights.id = passengers.flight_id
WHERE year = '2021'
AND month = '7'
AND day = '29';

-- Find the person with the following conditions:
-- 1. exied the bakery within 10 minutes at 10:15AM
-- 2. took a plane on 07-29-2021
-- 3. went to atm and withdraw money on 07-28-2021
-- 4. the original airport is 'Fiftyville'
-- 5. the earliest flight
SELECT DISTINCT(name) FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions atm ON bank_accounts.account_number = atm.account_number

JOIN bakery_security_logs bakery ON bakery.license_plate = people.license_plate

JOIN phone_calls ON phone_calls.caller = people.phone_number

JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = flights.origin_airport_id

AND atm.month = '7' AND atm.day = '28' AND atm.year = '2021' AND atm.atm_location = 'Leggett Street' AND atm.transaction_type = 'withdraw'
AND bakery.month = '7' AND bakery.day = '28' AND bakery.year = '2021' AND bakery.hour = '10' AND bakery.minute <= '25' AND bakery.activity = 'exit'
AND phone_calls.month = '7' AND phone_calls.day = '28' AND phone_calls.year = '2021' AND phone_calls.duration <= 60
WHERE flights.year = '2021' AND flights.month = '7' AND flights.day = '29'
AND airports.city = 'Fiftyville'
ORDER BY flights.hour ASC
LIMIT 1;

-- +-------+
-- | name  |
-- +-------+
-- | Diana |
-- | Bruce |
-- +-------+
-- Diana Bruce are the suspects



-- Pusrpose
-- find the person who talk to Diana within 1 minute

SELECT * FROM passengers
JOIN people ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE people.name = 'Bruce'
AND flights.day = '29';


SELECT * FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE people.name = 'Bruce'
AND phone_calls.day = '28'
AND phone_calls.duration < '60';
-- Dedection Bruce are the suspects



-- Purpose: find the person phoned with 'Bruce'
SELECT * FROM people
WHERE people.phone_number IN(
SELECT phone_calls.receiver FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE people.name = 'Bruce'
AND phone_calls.day = '28'
AND phone_calls.duration < '60'
);


-- Purpose: find the person who made a phone_call with 'Bruce'
SELECT p_receiver.name FROM phone_calls pc
JOIN people p_caller ON p_caller.phone_number = pc.caller
JOIN people p_receiver ON p_receiver.phone_number = pc.receiver
WHERE p_caller.name = 'Bruce'
AND pc.day = 28
AND pc.duration < 60;



-- Purpos: find the place Where Burece go

SELECT city FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON people.passport_number = passengers.passport_number
WHERE people.name = 'Bruce'
AND flights.month = '7' AND flights.day = '29' AND flights.year = '2021';



SELECT * FROM phone_calls
JOIN people p_caller ON p_caller.phone_number = phone_calls.caller
JOIN people p_receiver ON p_receiver.phone_number = phone_calls.receiver
WHERE p_caller.name = 'Bruce'
AND phone_calls.day = '28' AND phone_calls.duration <= 60;
