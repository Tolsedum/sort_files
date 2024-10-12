# sort_files
sort file in folder


--path_name  - The folder from which to sort files    
--types_sort - Types of file sorting    
        date_in_path      - takes file data from the directory structure (year/month/day.month.year)    
        date_in_file_name - takes the creation date of the file from its name (row_date_number in order)    
        timestamp         - the name of the file is the type of timestamp    
        meta_date         - date getting from file metadata    
        params            - taking the date from the file parameters (doesn't always work)    
--params_dir - sort by type 'params' in a separate folder    
--rename_file - move a file    
