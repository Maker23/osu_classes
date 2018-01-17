SELECT
dbjoin.bookID, dbjoin.bookTitle, dbjoin.authorName ,Group_concat(characterName) as Characters FROM


(
SELECT 
O.id as bookID, O.title as bookTitle, O.genre, O.publication_date, 
concat_ws (' ',A.title, A.fname, A.mnames,A.lname) as authorName,
M.description,M.date,
concat_ws (', ',concat_ws(' ', L.address, L.street),L.city, L.country) as location,
concat_ws (' ', K.title,K.fname,K.lname) as characterName
from opus O
inner join opus_author OA on O.id = OA.oid
inner join author A on A.id = OA.aid
inner join 
	(select * from moment where description='PRIMARY') M on O.id = M.oid
inner join location L on M.lid = L.id
inner join karacter_moment KM on M.id = KM.mid
inner join karacter K on K.id = KM.kid
) dbjoin


GROUP By bookID
;

