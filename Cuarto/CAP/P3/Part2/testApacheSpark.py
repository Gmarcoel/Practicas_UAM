# As a last part, a Python script that performs a basic test on Apache Spark should be
# provided. It is important to pay attention to the creation of the SparkSession.
APP_NAME="MyApp"
SPARK_URL="http://143.244.166.129:30077"

spark = SparkSession.builder.appName(APP_NAME).master(SPARK_URL) \
.config("spark.driver.host", "80.39.152.80") \
.getOrCreate()

sc = spark.sparkContext


data = ["Hello","we","were","unable",
"to","make","Docker","work","because",
"it","is","impossible"]

rdd=sc.parallelize(data)
rdd2=rdd.map(lambda x: (x,1))
for element in rdd2.collect():
    print(element)
