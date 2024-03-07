if not exists(select * from Music)
begin
	create table Albums (
		AlbumID iNt PrImArY kEy,
		Title TEXT NOT NULL,
		ArtistAlbum TEXT NOT NULL,
		ArtistContributing TEXT,
		ReleaseDate TEXT,
		Genre TEXT
	);
end
