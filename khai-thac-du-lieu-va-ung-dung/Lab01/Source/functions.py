import pandas as pd
import math

# Câu 1
def missing_columns(file_path):
    # Đọc DataFrame từ tập tin
    df = pd.read_csv(file_path)
    # Tách bộ dữ liệu thành danh sách chứa các thuộc tính
    columns = df.columns.tolist()
    # Duyệt qua từng cột trong DataFrame và tính số lượng giá trị null
    missing_values_count = {}
    for col in columns:
        col_data = df[col]
        num_missing = sum(col_data.isnull())
        missing_values_count[col] = num_missing
    # Liệt kê các cột bị thiếu dữ liệu
    missing_columns = {k:v for k,v in missing_values_count.items() if v!=0}
    return missing_columns

# Câu 2
def count_mising_lines(file_path):
    df = pd.read_csv(file_path)
    lines = 0
    for i in range(len(df)):
        # Kiểm tra nếu dòng i có vị trí nào bị thiếu dữ liệu
        if df.iloc[i].isnull().any():
            lines += 1
    return lines

# Câu 3
def fill_mising_values(args):
    # Đọc file CSV vào dataframe
    df = pd.read_csv(args.file_path)
    #df = pd.DataFrame(data)
    # Thực hiện điền giá trị thiếu bằng phương pháp được chỉ định
    for col in args.columns:
        if args.method == 'mean':
            mean_col = mean([val for val in df[col].tolist() if pd.notna(val)])
            df[col] = df[col].apply(lambda x: mean_col if pd.isna(x) else x)
            print('mean of',col,':', str(mean_col))
        elif args.method == 'median':
            median_col = median([val for val in df[col].tolist() if pd.notna(val)])
            df[col] = df[col].apply(lambda x: median_col if pd.isna(x) else x)
            print('median of',col,':', str(median_col))
        elif args.method == 'mode':
            mode_col = mode([val for val in df[col].tolist() if pd.notna(val)])
            df[col] = df[col].apply(lambda x: mode_col if pd.isna(x) else x)
            print('mode of',col,':', str(mode_col))
    # Ghi dataframe đã điền giá trị thiếu vào file
    df.to_csv(args.out, index=False)
    return df
def mean(data):
    # Tính trung bình cộng
    return sum(data) / len(data)
def median(data):
    # Tính trung vị
    sorted_data  = sorted(data)
    n = len(data)
    if n % 2 == 0:
        return (sorted_data[n//2-1] + sorted_data[n//2]) / 2
    else:
        return sorted_data[n//2]
def mode(data):
    #Tính mode
    f = {}
    for x in data:
        if x in f:
            f[x] += 1
        else:
            f[x] = 1
    max_f = max(f.values())
    mode = [x for x in f if f[x] == max_f]
    return mode[0]

# Câu 4
def delete_missing_rows(args):
    # Đọc file CSV vào dataframe
    df = pd.read_csv(args.file_path)
    print("Số hàng ban đầu là:", df.shape[0])
    threshold = math.ceil(len(df.columns) * args.percentage/100)
    for i, row in df.iterrows():
        if row.isna().sum() > threshold:
            df = df.drop(i)
    print("Số hàng sau khi làm sạch là:", df.shape[0])
    df.to_csv(args.out, index=False)
    return df
# Câu 5:
def delete_missing_columns(args):
    # Đọc file CSV vào dataframe
    df = pd.read_csv(args.file_path)
    print("Số cột ban đầu là:", df.shape[1])
    missing_values = df.isna().sum()
    missing_percentage = (missing_values / len(df)) * 100
    columns_to_drop = missing_percentage[missing_percentage > args.percentage].index
    df = df.drop(columns_to_drop, axis=1)
    print("Số cột sau khi làm sạch là:", df.shape[1])
    df.to_csv(args.out, index=False)
    return df
# Câu 6:
def delete_duplicates(args):
    # Đọc file CSV vào dataframe
    df = pd.read_csv(args.file_path)
    print("Số mẫu ban đầu là:", df.shape[0])
    duplicates = []
    for i in range(len(df)):
        for j in range(i+1, len(df)):
            if df.iloc[i].equals(df.iloc[j]):
                duplicates.append(j)
    df = df.drop(duplicates)
    print("Số mẫu sau khi xoá trùng lặp là:", df.shape[0])
    df.to_csv(args.out, index=False)
    return df

# Câu 7:
def normalize(args):
    # Đọc file CSV vào dataframe
    df = pd.read_csv(args.file_path)
    #df = pd.DataFrame(data)
    for col in args.columns:
        if args.method == 'min-max':
            min_col = df[col].min()
            max_col = df[col].max()
            df[col] = (df[col] - min_col) / (max_col - min_col)
        elif args.method == 'z-score':
            mean_col = mean([val for val in df[col].tolist() if pd.notna(val)])
            std_col = std([val for val in df[col].tolist() if pd.notna(val)],mean_col)
            df[col] = (df[col] - mean_col) / std_col
    df.to_csv(args.out, index=False)
    return df
def std(data,mean):
    n = len(data)
    variance = sum((x - mean) ** 2 for x in data) / (n-1)
    std = variance ** 0.5
    return std

# Câu 8
def performing(args):
    # Đọc file CSV vào dataframe
    df = pd.read_csv(args.file_path)
    col1 = args.columns[0]
    col2 = args.columns[1]

    if args.method == 'sum':
        df[args.newcolumn] = df[col1] + df[col2]
    elif args.method == 'sub':
        df[args.newcolumn] = df[col1] - df[col2]
    elif args.method == 'mul':
        df[args.newcolumn] = df[col1] * df[col2]
    elif args.method == 'div':
        df[args.newcolumn] = df[col1] / df[col2]
    return df