--
-- PostgreSQL database dump
--

-- Dumped from database version 16.0
-- Dumped by pg_dump version 16.0

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: parent; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.parent (
    id integer NOT NULL,
    lastname character varying(255),
    name character varying(255),
    surname character varying(255),
    address character varying(255),
    relation_degree character varying(255)
);


ALTER TABLE public.parent OWNER TO admin;

--
-- Name: parent_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.parent_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.parent_id_seq OWNER TO admin;

--
-- Name: parent_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.parent_id_seq OWNED BY public.parent.id;


--
-- Name: performance; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.performance (
    id integer NOT NULL,
    student_id integer,
    year character varying(255),
    class integer,
    subject character varying(255),
    quarterly_grade integer,
    semester_grade integer,
    annual_grade integer,
    examination_grade integer,
    final_grade integer
);


ALTER TABLE public.performance OWNER TO admin;

--
-- Name: performance_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.performance_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.performance_id_seq OWNER TO admin;

--
-- Name: performance_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.performance_id_seq OWNED BY public.performance.id;


--
-- Name: student; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.student (
    id integer NOT NULL,
    lastname character varying(255),
    name character varying(255),
    surname character varying(255),
    address character varying(255),
    birth_date character varying(255),
    class integer,
    entry_year character varying(255)
);


ALTER TABLE public.student OWNER TO admin;

--
-- Name: student_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.student_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.student_id_seq OWNER TO admin;

--
-- Name: student_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.student_id_seq OWNED BY public.student.id;


--
-- Name: students_to_parents; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.students_to_parents (
    id integer NOT NULL,
    student_id integer,
    parent_id integer
);


ALTER TABLE public.students_to_parents OWNER TO admin;

--
-- Name: students_to_parents_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.students_to_parents_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.students_to_parents_id_seq OWNER TO admin;

--
-- Name: students_to_parents_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.students_to_parents_id_seq OWNED BY public.students_to_parents.id;


--
-- Name: parent id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.parent ALTER COLUMN id SET DEFAULT nextval('public.parent_id_seq'::regclass);


--
-- Name: performance id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.performance ALTER COLUMN id SET DEFAULT nextval('public.performance_id_seq'::regclass);


--
-- Name: student id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.student ALTER COLUMN id SET DEFAULT nextval('public.student_id_seq'::regclass);


--
-- Name: students_to_parents id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.students_to_parents ALTER COLUMN id SET DEFAULT nextval('public.students_to_parents_id_seq'::regclass);


--
-- Data for Name: parent; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.parent (id, lastname, name, surname, address, relation_degree) FROM stdin;
1	Ivanov	Petr	Andreevich	Krasnaya 22, 32	Father
2	Smith	Olivia	Park	567 Maple Street, Boston, MA	Mother
3	Miller	James	Davis	890 Birch Avenue, Phoenix, AZ	Father
4	Harris	Chloe	Tobias	432 Willow Road, Austin, TX	Mother
5	Martin	Liam	German	765 Redwood Drive, San Francisco, CA	Father
6	Jones	Ava	Kim	321 Birch Lane, New York, NY	Mother
\.


--
-- Data for Name: performance; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.performance (id, student_id, year, class, subject, quarterly_grade, semester_grade, annual_grade, examination_grade, final_grade) FROM stdin;
9	13	2023	10	Science	85	89	88	91	88
10	14	2023	9	History	78	82	80	85	81
12	16	2023	8	Art	75	77	79	81	78
13	14	2023	9	Math	77	79	74	80	82
11	15	2023	7	English	92	91	88	90	89
\.


--
-- Data for Name: student; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.student (id, lastname, name, surname, address, birth_date, class, entry_year) FROM stdin;
13	Johnson	Alice	Miller	456 Elm Street	2004-08-20	10	2022
14	Brown	Michael	Wilson	789 Oak Street	2003-02-25	9	2021
16	Wilson	Sophia	Anderson	222 Cedar Street	2007-06-05	8	2022
18	Panaev	Alex	Nicolaevich	27 Belousova	2002-01-17	5	2020
15	Davis	Emily	Clark	102 Pine Street	2006-11-10	7	2022
\.


--
-- Data for Name: students_to_parents; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.students_to_parents (id, student_id, parent_id) FROM stdin;
5	16	5
1	13	2
\.


--
-- Name: parent_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.parent_id_seq', 6, true);


--
-- Name: performance_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.performance_id_seq', 13, true);


--
-- Name: student_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.student_id_seq', 18, true);


--
-- Name: students_to_parents_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.students_to_parents_id_seq', 5, true);


--
-- Name: parent parent_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.parent
    ADD CONSTRAINT parent_pkey PRIMARY KEY (id);


--
-- Name: performance performance_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.performance
    ADD CONSTRAINT performance_pkey PRIMARY KEY (id);


--
-- Name: student student_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.student
    ADD CONSTRAINT student_pkey PRIMARY KEY (id);


--
-- Name: students_to_parents students_to_parents_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.students_to_parents
    ADD CONSTRAINT students_to_parents_pkey PRIMARY KEY (id);


--
-- Name: performance performance_student_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.performance
    ADD CONSTRAINT performance_student_id_fkey FOREIGN KEY (student_id) REFERENCES public.student(id);


--
-- Name: students_to_parents students_to_parents_parent_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.students_to_parents
    ADD CONSTRAINT students_to_parents_parent_id_fkey FOREIGN KEY (parent_id) REFERENCES public.parent(id);


--
-- Name: students_to_parents students_to_parents_student_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.students_to_parents
    ADD CONSTRAINT students_to_parents_student_id_fkey FOREIGN KEY (student_id) REFERENCES public.student(id);


--
-- PostgreSQL database dump complete
--

